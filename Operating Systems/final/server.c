#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_SIZE 256

// Define the employee_info struct
struct employee_info {
    char ID[7];
    char name[10];
    double salary;
};

// Create a static array of employee_info
struct employee_info DB[10] = {
    {"abc123", "Hassan", 100000.0},
    {"def456", "Ali", 50000.0},
    {"ghi789", "Hammad", 75000.0},
    {"jkl012", "Shaheen", 80000.0},
    {"mno345", "Basim", 55000.0},
    {"pqr678", "Haroona", 60000.0},
    {"stu901", "Desmond", 65000.0},
    {"vwx234", "Emad", 70000.0},
    {"yza567", "Faiz", 90000.0},
    {"bcd890", "Ghuffran", 95000.0}
};

// Function to handle client requests
void handle_client_request(int client_socket) {
    char buffer[MAX_SIZE];
    int bytes_received;
    int bytes_sent;
    char id[7];
    int found;

    // Receive message from client
    bytes_received = recv(client_socket, buffer, MAX_SIZE, 0);
    if (bytes_received < 0) {
        perror("Error receiving data from client");
        exit(1);
    }
    buffer[bytes_received] = '\0';

    // Check if the message is "STOP"
    if (strcmp(buffer, "STOP") == 0) {
        printf("Received STOP message from client\n");
        close(client_socket);
        exit(0);
    }

    // Check if the message is "GETSALARY ID"
    if (sscanf(buffer, "GETSALARY %s", id) == 1) {
        found = 0;

        // Search the employee_info array for the given ID
        for (int i = 0; i < 10; i++) {
            if (strcmp(DB[i].ID, id) == 0) {
                found = 1;

                // Create reply message containing employee name and salary
                char reply[MAX_SIZE];
                snprintf(reply, MAX_SIZE, "Employee name: %s\nEmployee salary: %.2f", DB[i].name, DB[i].salary);

                // Send reply message to client
                bytes_sent = send(client_socket, reply, strlen(reply), 0);
                if (bytes_sent < 0) {
                    perror("Error sending data to client");
                    exit(1);
                }
                break;
            }
        }

        // If the ID is not found, send an error message
        if (!found) {
            char error_msg[MAX_SIZE] = "Employee not found";
            bytes_sent = send(client_socket, error_msg, strlen(error_msg), 0);
            if (bytes_sent < 0) {
              perror("Error sending data to client");
              exit(1);
            }
            else if (bytes_sent != strlen(error_msg)) {
              fprintf(stderr, "Incomplete data sent to client.\n");
              exit(1);
            }
        }
        else {
           // If the message is not recognized, send an error message
            char error_msg[MAX_SIZE] = "Invalid message format";
            bytes_sent = send(client_socket, error_msg, strlen(error_msg), 0);
            if (bytes_sent < 0) {
                perror("Error sending data to client");
                exit(1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[MAX_SIZE];
    pid_t pid;

    // check the command-line arguments
    if (argc < 2) {
        fprintf(stderr, "ERROR: no port provided\n");
        exit(1);
    }

    // create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR: Failed in creating and opening socket\n");
        exit(1);
    }

    // set the server address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR: Binding socket failed\n");
        exit(1);
    }

    // listen for incoming connections
    listen(sockfd, 5);

    while (1) {
        // accept a new client connection
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR: Couldn't accept new client connection.\n\n");
            exit(1);
        }

        // fork a new process to serve the client
        pid = fork();
        if (pid < 0) {
            perror("ERROR: Forking process isn't working\n");
            exit(1);
        }
        if (pid == 0) {
            // child process
            close(sockfd); // close the parent socket in child process
            handle_client_request(newsockfd); // handle client requests
            exit(0);
        } else {
            // parent process
            close(newsockfd); // close the child socket in parent process
        }
    }

    close(sockfd); // close the server socket
    return 0;
}