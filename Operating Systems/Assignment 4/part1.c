#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define MAX_SIZE 1000000

double A_arr[MAX_SIZE];
double B_arr[MAX_SIZE];
double C_arr[MAX_SIZE];
double A_firsthalf_arr[MAX_SIZE/2];
double A_secondhalf_arr[MAX_SIZE/2];

// struct for sorting array arguments
struct sortArrayArgs {
	double *arr;
	int size;
};

// struct for merging array arguments
struct mergeArrayArgs {
	double* arr1;
	int arr1_size;
	double* arr2;
	int arr2_size;
	double* final_arr;
};

// Sorts the array
void *sort_Array(void *arg) {
    struct sortArrayArgs *args = (struct sortArrayArgs *)arg;
    double *A_arr = args->arr;
    int start = 0;
    int end = args->size;
    int i, j;
    for (i = start; i < end; i++) {
        for (j = i + 1; j < end; j++) {
            if (A_arr[j] < A_arr[i]) {
                double temp = A_arr[j];
                A_arr[j] = A_arr[i];
                A_arr[i] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

// Merges the subsets into a complete sorted array
void *merge_Array(void *arg) {
    struct mergeArrayArgs *args = (struct mergeArrayArgs *)arg;
    double *A_firsthalf_arr = args->arr1;
    int A_firsthalf_arrSize = args->arr1_size;
    double *A_secondhalf_arr = args->arr2;
    int A_secondhalf_arrSize = args->arr2_size;
    double *C_arr = args->final_arr;
    int mid = A_firsthalf_arrSize;
    int i = 0, j = 0, k = 0;
    while (i < mid && j < A_secondhalf_arrSize) {
        if (A_firsthalf_arr[i] < A_secondhalf_arr[j]) {
            C_arr[k] = A_firsthalf_arr[i];
            i++;
        }
        else {
            C_arr[k] = A_secondhalf_arr[j];
            j++;
        }
        k++;
    }
    while (i < mid) {
        C_arr[k++] = A_firsthalf_arr[i++];
    }
    while (j < A_secondhalf_arrSize) {
        C_arr[k++] = A_secondhalf_arr[j++];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

	// Checks the number of parameters being used
	if (argc != 2) {
		printf("Usage: %s <size>\n", argv[0]);
		return -1;
	}
	
	int size = atoi(argv[1]);

	// Checks if the size is less than the maximum size of the array
	if(size > MAX_SIZE) {
		printf("Error: Array size is much bigger than %d\n", MAX_SIZE);
		return -1;
	}

	// Creates random numbers to fill in A_arr, while creating B_arr and C_arr
	srand(time(NULL));
	for(int i = 0; i < size; i++) {
	    A_arr[i] = (double)(rand()%1000 + 1);
	    B_arr[i] = 0.0;
	    C_arr[i] = 0.0;
	}

	// Copies the first and second halves of A into their respective arrays
	double* A_firsthalf_arr = malloc((size/2) * sizeof(double));
	double* A_secondhalf_arr = malloc((size/2) * sizeof(double));
	memcpy(A_firsthalf_arr, A_arr, (size/2) * sizeof(double));
	memcpy(A_secondhalf_arr, A_arr + size/2, (size/2) * sizeof(double));

	// Creating the time values for the starting and ending time for sorting the array, as well as creating the variable for elapsed time
	struct timespec ts_begin, ts_end;
	double elapsed;

	// Copy A_arr into C_arr
	double* C_arr = malloc(size * sizeof(double));
	memcpy(C_arr, A_arr, size * sizeof(double));

	// Starting the sorting with 2 threads
	clock_gettime(CLOCK_MONOTONIC, &ts_begin);

	// Creating threads to sort A_firsthalf_arr and A_secondhalf_arr
	struct sortArrayArgs args1 = {A_firsthalf_arr, size/2};
	struct sortArrayArgs args2 = {A_secondhalf_arr, size/2};
	pthread_t temp_A1, temp_A2;
	pthread_create(&temp_A1, NULL, sort_Array, &args1);
	pthread_create(&temp_A2, NULL, sort_Array, &args2);

	// Joining the threads to finish sorting
	pthread_join(temp_A1, NULL);
	pthread_join(temp_A2, NULL);

	// Create thread to merge both halves into C_arr
	pthread_t mergedArray;
	struct mergeArrayArgs argsM = {A_firsthalf_arr, size/2, A_secondhalf_arr, size/2, C_arr};
	pthread_create(&mergedArray, NULL, merge_Array, &argsM);

	// Joining the thread to finish sorting
	pthread_join(mergedArray, NULL);
	clock_gettime(CLOCK_MONOTONIC, &ts_end);

	// Records the elapsed time taken and prints it
	elapsed = (ts_end.tv_sec - ts_begin.tv_sec);
	elapsed += (ts_end.tv_nsec - ts_begin.tv_nsec) / 1000000000.0;
	printf("Sorting is done in %.1fms when two threads are used\n", (elapsed*1000.0));

	// Copy A_arr into B_arr
	double* B_arr = malloc(size * sizeof(double));
	memcpy(B_arr, A_arr, size * sizeof(double));

	// Sorting with just one thread
	clock_gettime(CLOCK_MONOTONIC, &ts_begin);
	pthread_t sorted;
	struct sortArrayArgs args = {B_arr, size};
	pthread_create(&sorted, NULL, sort_Array, &args);
	pthread_join(sorted, NULL);
	clock_gettime(CLOCK_MONOTONIC, &ts_end);

	// Records the elapsed time taken and prints it
	elapsed = (ts_end.tv_sec - ts_begin.tv_sec);
	elapsed += (ts_end.tv_nsec - ts_begin.tv_nsec) / 1000000000.0;
	printf("Sorting is done in %.1fms when one thread is used\n", (elapsed*1000.0));

	return 0;
}