#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

struct PCB {
	int PID, PR;
	int numCPUBurst, numIOBurst;
	int *CPUBurst, *IOBurst; // for creating dynamic arrays to store cpu and io burst times
	int cpuindex, ioindex;
    struct timespec ts_begin, ts_end;
	struct PCB *prev, *next;
};

// global variables
struct PCB *Ready_Q = NULL, *IO_Q = NULL;
int file_read_done = 0, cpu_sch_done = 0, io_sys_done = 0, cpu_busy = 0, io_busy = 0;
sem_t sem_cpu, sem_io;
int cpu_utilization_time = 0;
int total_time = 0;
int processes = 0;
int total_turnaround_time = 0;
int total_waiting_time = 0;

void* File_thread(void* arg);
void* CPU_thread(void* arg);
void* IO_thread(void* arg);
void thread_performance();

int main(int argc, char const *argv[]) {
    /* process command line args */
    if (argc < 4) {
        fprintf(stderr, "Usage: %s -alg [FIFO|SJF|PR|RR] [-quantum [integer(ms)]] -input [file name]\n", argv[0]);
        return 1;
    }

    char* alg = argv[1];
    int quantum = atoi(argv[2]);
    char* file = argv[3];

    // create/initialize the necessary data structures
    Ready_Q = NULL;
    IO_Q = NULL;
    file_read_done = 0;
    cpu_sch_done = 0;
    io_sys_done = 0;
    cpu_busy = 0;
    io_busy = 0;
    sem_init(&sem_cpu, 0, 0);
    sem_init(&sem_io, 0, 0);

	// Creating and starting each thread
	pthread_t file_thread, cpu_thread, io_thread;
	pthread_create(&file_thread, NULL, File_thread, NULL);
	pthread_create(&cpu_thread, NULL, CPU_thread, NULL);
	pthread_create(&io_thread, NULL, IO_thread, NULL);

	// Waiting for threads to finish
	pthread_join(file_thread, NULL);
	pthread_join(cpu_thread, NULL);
	pthread_join(io_thread, NULL);

    // Prints the performance metrics
	thread_performance();

	// clean up
    sem_destroy(&sem_cpu);
    sem_destroy(&sem_io);

    return 0;
}

void* File_thread(void* arg) {
    char* file = (char*) arg;
    FILE* fp = fopen(file, "r");

    if (fp == NULL) {
        printf("Error: File does not exist!\n", file);
        return NULL;
    }

    int currPID = 0;
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp) != NULL) {
        char* token = strtok(line, " \n");
        if (strcmp(token, "proc") == 0) {
            struct PCB* newPCB = (struct PCB*)malloc(sizeof(struct PCB));
            newPCB->PID = currPID++;
            newPCB->prev = NULL;
            newPCB->next = NULL;
            clock_gettime(CLOCK_MONOTONIC, &newPCB->ts_begin);

            token = strtok(NULL, " \n");
            newPCB->PR = atoi(token);

            token = strtok(NULL, " \n");
            newPCB->numCPUBurst = atoi(token);
            newPCB->CPUBurst = malloc(sizeof(int) * newPCB->numCPUBurst);
            newPCB->cpuindex = 0;

            token = strtok(NULL, " \n");
            newPCB->numIOBurst = atoi(token);
            newPCB->IOBurst = malloc(sizeof(int) * newPCB->numIOBurst);
            newPCB->ioindex = 0;

            for (int i = 0; i < newPCB->numCPUBurst + newPCB->numIOBurst; i++) {
                token = strtok(NULL, " \n");
                if (i % 2 == 0) {
                    newPCB->CPUBurst[newPCB->cpuindex++] = atoi(token);
                } else {
                    newPCB->IOBurst[newPCB->ioindex++] = atoi(token);
                }
            }

            sem_wait(&sem_ready);
            insertPCB(newPCB, &Ready_Q);
            sem_post(&sem_cpu);
        } else if (strcmp(token, "sleep") == 0) {
            token = strtok(NULL, " \n");
            int ms = atoi(token);
            usleep(ms * 1000);
        } else if (strcmp(token, "stop") == 0) {
            break;
        }
    }

    file_read_done = 1;
    fclose(fp);
    return NULL;
}


void* CPU_thread(void* arg) {
    int res;
    struct timespec atimespec = {1, 0}; // 1 second timeout

    while (1) {
        // Check if all queues are empty and file reading is done
        if (is_empty(Ready_Q) && !cpu_busy && is_empty(IO_Q) && !io_busy && file_read_done) {
            break;
        }

        // Wait for a signal from the semaphore, depending on the scheduling algorithm
        if (strcmp(alg, "FIFO") == 0 || strcmp(alg, "RR") == 0 || strcmp(alg, "PR") == 0) {
            res = sem_timedwait(&sem_cpu, &atimespec);
        } else if (strcmp(alg, "SJF") == 0) {
            res = sem_wait(&sem_cpu);
        }

        if (res == -1 && errno == ETIMEDOUT) {
            continue;
        }

        // Get the PCB with the shortest CPU burst time or highest priority
        struct PCB* curr_PCB = Ready_Q;
        struct PCB* short_PCB = NULL;

        while (curr_PCB != NULL) {
            if (shortPCB == NULL) {
                short_PCB = curr_PCB;
            } else if (strcmp(alg, "SJF") == 0 && curr_PCB->CPUBurst[curr_PCB->cpuindex] < short_PCB->CPUBurst[short_PCB->cpuindex]) {
                short_PCB = curr_PCB;
            } else if (strcmp(alg, "PR") == 0 && curr_PCB->PR > short_PCB->PR) {
                short_PCB = curr_PCB;
            }

            curr_PCB = curr_PCB->next;
        }

        cpu_busy = 1;

        if (curr_PCB != NULL) {
            if (Ready_Q == NULL || curr_PCB == NULL) {
                return;
            }

            // If the current PCB is the head of the queue, update the head
            if (Ready_Q == curr_PCB) {
                Ready_Q = Ready_Q->next;
            }

            // Update the pointers of the surrounding PCBs
            if (curr_PCB->prev != NULL) {
                curr_PCB->prev->next = curr_PCB->next;
            }

            if (curr_PCB->next != NULL) {
                curr_PCB->next->prev = curr_PCB->prev;
            }

            // Clear the pointers of the current PCB
            curr_PCB->prev = NULL;
            curr_PCB->next = NULL;

            Ready_Q.size()--;

            // Simulate the CPU burst time
            usleep(curr_PCB->CPUBurst[curr_PCB->cpuindex] * 1000); // in microseconds
            curr_PCB->cpuindex++;

            if (curr_PCB->cpuindex >= curr_PCB->numCPUBurst) {
                free(curr_PCB);
                cpu_busy = 0;
            } else {
                if (strcmp(alg, "FIFO") == 0 || strcmp(alg, "SJF") == 0) {
                    // Add the process back to the end of the Ready Queue
                    insert_PCB(curr_PCB);
                } else if (strcmp(alg, "RR") == 0) {
                    // Add the process back to the end of the Ready Queue if it hasn't used up its time slice
                    if (curr_PCB->quantum > 0) {
                        insert_PCB(curr_PCB);
                    } else {
                        // Reset the quantum if it has been used up
                        curr_PCB->quantum = quantum;
                        // Add the process back to the end of the Ready Queue only if there are no I/O requests
                        if (is_empty(IO_Q)) {
                            insert_PCB(curr_PCB);
                        } else {
                            // Otherwise, add it to the front of the I/O Queue
                            insert_PCB_IO(curr_PCB);
                        }
                    }
                } else if (strcmp(alg, "PR") == 0) {
                    // Add the process back to the Ready Queue based on its priority
                    insert_PCB(curr_PCB);
                }
                cpu_busy = 0;
            }
        }
        cpu_sch_done = 1;
    }
    pthread_exit(NULL);
}


void *IO_thread(void *arg) {
    int res;
    struct timespec atimespec = {1, 0};

    while(1) {
        // Check if there are any PCBs in the Ready Queue or IO Queue
        if (is_empty(Ready_Q) && is_empty(IO_Q) && !cpu_busy && file_read_done) {
            break;
        }
        
        // Wait for IO semaphore
        res = sem_timedwait(&sem_io, &atimespec);
        if (res == -1 && errno == ETIMEDOUT) {
            continue;
        }
        
        // Set IO flag to indicate that IO operation is being performed
        io_busy = 1;
        
        // Get the PCB based on the scheduling algorithm from IO_Q
        if (strcmp(alg, "SJF") == 0) {
            PCB* shortest_job = NULL;
            int shortest_time = -1;

            for (int i = 0; i < IO_Q.size(); i++) {
                if (shortest_job == NULL || io_q[i]->io_time < shortest_time) {
                    shortest_job = io_q[i];
                    shortest_time = io_q[i]->io_time;
                }
            }

            return shortest_job;
        } 
        else if (strcmp(alg, "RR") == 0) {
            if (!is_empty(IO_Q)) {
                PCB* next_pcb = dequeue(IO_Q);
                if (next_pcb->ioindex >= next_pcb->ionum) {
                    free(next_pcb->IOBurst);
                    free(next_pcb->CPUBurst);
                    free(next_pcb);
                } else {
                    enqueue(IO_Q, next_pcb);
                }
                return next_pcb;
            }
            return NULL;
        } else if (strcmp(alg, "PR") == 0) {
            if (!is_empty(IO_Q)) {
                // Set the first PCB in the IO queue as the highest priority
                PCB* high = IO_Q;

                // Iterate through each PCB in the IO queue
                for (PCB* pcb : IO_Q) {
                    if (pcb->priority > high->priority) {
                        high = pcb;
                    }
                }
                dequeue(IO_Q, high);
                return high;
            }
            return NULL;
        } else {
            // Default to FIFO if scheduling algorithm is not recognized
            if (!is_empty(IO_Q)) {
                PCB* pcb = IO_Q.front();
                dequeue(IO_Q, pcb);
                return pcb;
            }
            return NULL;
        }
        
        // Perform IO operation
        usleep(pcb->IOBurst[pcb->ioindex] * 1000);
        
        // Update PCB and Ready Queue
        pcb->ioindex++;

        // Inserting PCB into Ready_Q depending on each algorithm
        if (strcmp(alg, "SJF") == 0 || strcmp(alg, "PR") == 0) {
            if (is_empty(Ready_Q)) {
                pcb->next = Ready_Q;
                Ready_Q = pcb;
            } else {
                int pcb_time = pcb->CPUBurst[pcb->cpuindex];
                bool inserted = false;

                for (int i = 0; i < Ready_Q_size; i++) {
                    PCB* curr = getReadyQ(i);
                    int curr_time;

                    if (strcmp(alg, "SJF") == 0) {
                        curr_time = curr->CPUBurst[curr->cpuindex];
                    } else if (strcmp(alg, "PR") == 0) {
                        curr_time = curr->priority;
                    }

                    if (pcb_time < curr_time) {
                        // Inserts PCB into Ready_Q
                        inserted = true;
                        break;
                    }
                }

                if (!inserted) {
                    pushBackReadyQ(pcb);
                }
            }

        } else if (strcmp(alg, "RR") == 0) {
            // Inserts PCB into Ready_Q with Round Robin
        } else {
            // Default to FIFO if scheduling algorithm is not recognized
            // Inserts PCB into Ready_Q with FIFO
        }
        
        // Set IO flag to indicate that IO operation is complete
        io_busy = 0;
        
        // Signal CPU semaphore to indicate that CPU is available
        sem_post(&sem_cpu);
        
        // Set IO system done flag to indicate that IO system is idle
        io_sys_done = 1;
    }
    pthread_exit(NULL);
}


void thread_performance(){
    // Calculate and print performance metrics
    printf("Input File Name              : %s\n", file);
    printf("CPU Scheduling Alg           : %s", alg);
    if (strcmp(alg, "RR") == 0) {
        printf("(%d)", quantum);
    }
    printf("\n");

    float cpu_utilization = ((float)cpu_utilization_time / (float)total_time) * 100.0;
    float throughput = (float)processes / ((float)total_time / 1000.0);
    float avg_turnaround_time = (float)total_turnaround_time / (float)processes;
    float avg_waiting_time = (float)total_waiting_time / (float)processes;

    printf("CPU utilization              : %.2f%%\n", cpu_utilization);
    printf("Throughput                   : %.2f\n", throughput);
    printf("Avg. Turnaround time         : %.2f ms\n", avg_turnaround_time);
    printf("Avg. Waiting time in R queue : %.2f ms\n", avg_waiting_time);
}

// helper function for inserting PCB into Ready_Q
void insert_PCB(PCB *curr_PCB) {

    // Set the next of the PCB to NULL
    curr_PCB->next = NULL;
    
    // If Ready_Q is empty, add the PCB as the head
    if (Ready_Q == NULL) {
        Ready_Q = curr_PCB;
    } 
    // Otherwise, add the PCB to the end of the list
    else {
        PCB *temp = Ready_Q;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = curr_PCB;
    } 
}

// helper function for inserting PCB into IO_Q
void insert_PCB_IO(PCB *curr_PCB) {
    
    // Set the next of the PCB to NULL
    curr_PCB->next = NULL;
    
    // If Ready_Q is empty, add the PCB as the head
    if (IO_Q == NULL) {
        IO_Q = curr_PCB;
    } 
    // Otherwise, add the PCB to the end of the list
    else {
        PCB *temp = Ready_Q;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = curr_PCB;
    } 
}