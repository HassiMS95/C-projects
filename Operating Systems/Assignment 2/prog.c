/*
 * File: prog.c
 * Hassan Sheikh
 *
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog.h"

void FIFO_scheduling() {
  while (Head != NULL) {

    // Removing PCB from the head of the linked list
    struct PCB_st *PCB = Head;
    Head = Head->next;
    if (Head == NULL) {
      Tail = NULL;
    }

    // Context switching
    for (int i = 0; i < 8; i++) {
      CPUreg[i] = PCB->myReg[i];
    }
    for (int i = 0; i < PCB->CPUburst; i++) {
      for (int j = 0; j < 8; j++) {
        CPUreg[j]++;
      }
    }
    for (int i = 0; i < 8; i++) {
      PCB->myReg[i] = CPUreg[i];
    }

    // Collecting data for scheduling performance
    PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
    Total_waiting_time = Total_waiting_time + PCB->waitingTime;
    CLOCK = CLOCK + PCB->CPUburst;
    Total_turnaround_time = Total_turnaround_time + CLOCK;
    Total_job = Total_job + 1;

    // Frees the PCB struct
    free(PCB);
  }

  // Printing performance metrics
  printf("Average Waiting time = %.2f ms\t(%d/%d)\n", (float)Total_waiting_time/Total_job, waitingTime, Total_job);
  printf("Average turnaround time = %.2f ms\t(%d/%d)\n", (float)Total_turnaround_time/Total_job, Total_turnaround_time, Total_job);
  printf("Throughput = %.2f jobs per ms\t(%d/%d)\n", (float)Total_job/CLOCK, Total_job, CLOCK);
}

void SJF_scheduling() {
  struct PCB_st *PCB_curr, *PCB_prev, *PCB_temp;
  while (Head != NULL) {
    // Finding the PCB with the shortest CPUburst
    PCB_curr = Head;
    PCB_prev = NULL;
    int shortBurst = PCB_curr->CPUburst;
    while (PCB_curr->next != NULL) {
      if (PCB_curr->next != NULL) {
        PCB_prev = PCB_curr;
        PCB_temp = PCB_curr->next;
        shortBurst = PCB_temp->CPUburst;
      }
      PCB_curr = PCB_curr->next;
    }
    if (PCB_prev != NULL) {
      PCB_temp = PCB_prev->next;
      PCB_prev->next = PCB_temp->next;
    }
    else {
      Head = PCB_temp->next;
    }

    //Context switching
    for (int i = 0; i < 8; i++) {
      PCB_temp->myReg[i] = CPUreg[i];
      CPUreg[i] = PCB_temp->myReg[i];
      CPUreg[i]++;
      PCB_temp->myReg[i] = CPUreg[i];
    }

    // Collecting data for scheduling performance
    PCB_temp->waitingTime = PCB_temp->waitingTime + CLOCK - PCB_temp->queueEnterClock;
    Total_waiting_time = Total_waiting_time + PCB_temp->waitingTime;
    CLOCK = CLOCK + PCB_temp->CPUburst;
    Total_turnaround_time = Total_turnaround_time + CLOCK;
    Total_job = Total_job + 1;

    // Frees the Temporary PCB
    free(PCB_temp);
  }

  // Printing performance metrics
  printf("Average Waiting time = %.2f ms\t(%d/%d)\n", (float)Total_waiting_time/Total_job, waitingTime, Total_job);
  printf("Average turnaround time = %.2f ms\t(%d/%d)\n", (float)Total_turnaround_time/Total_job, Total_turnaround_time, Total_job);
  printf("Throughput = %.2f jobs per ms\t(%d/%d)\n", (float)Total_job/CLOCK, Total_job, CLOCK);
}

void PR_scheduling() {

  // Searching through the linked list to find the process with the maximum value of ProcPR
  while (Head != NULL) {
    struct PCB_st *PCB_curr = Head;
    struct PCB_st *PCB_prev = NULL;
    struct PCB_st *PCB_prMax = Head;
    struct PCB_st *PCB_prPrev = NULL;
    while (PCB_curr != NULL) {
      if (PCB_curr->ProcPR > PCB_prMax->ProcPR) {
        PCB_prMax = PCB_curr;
        PCB_prPrev = PCB_prev;
      }
      PCB_prev = PCB_curr;
      PCB_curr = PCB_curr->next;
    }

    // Removes the process w/ the max value of ProcPR from the linked list.
    if (PCB_prMax == Head) {
      Head = PCB_prMax->next;
    }
    else {
      PCB_prPrev->next = PCB_prMax->next;
    }

    if (PCB_prMax == Tail) {
      Tail = PCB_prPrev;
    }

    // Context switching
    for (int i = 0; i < 8; i++) {
      CPUreg[i] = PCB_prMax->myReg[i];
    }
    for (int i = 0; i < PCB_prMax->CPUburst; i++) {
      for (int j = 0; j < 8; j++) {
        CPUreg[j]++;
      }
    }
    for (int i = 0; i < 8; i++) {
      PCB_prMax->myReg[i] = CPUreg[i];
    }

    // Collecting data for scheduling performance
    PCB_prMax->waitingTime = PCB_prMax->waitingTime + CLOCK - PCB_prMax->queueEnterClock;
    Total_waiting_time = Total_waiting_time + PCB_prMax->waitingTime;
    CLOCK = CLOCK + PCB_prMax->CPUburst;
    Total_turnaround_time = Total_turnaround_time + CLOCK;
    Total_job = Total_job + 1;


    // Frees the PCB
    free(PCB_prMax);
  }

  // Printing performance metrics
  printf("Average Waiting time = %.2f ms\t(%d/%d)\n", (float)Total_waiting_time/Total_job, waitingTime, Total_job);
  printf("Average turnaround time = %.2f ms\t(%d/%d)\n", (float)Total_turnaround_time/Total_job, Total_turnaround_time, Total_job);
  printf("Throughput = %.2f jobs per ms\t(%d/%d)\n", (float)Total_job/CLOCK, Total_job, CLOCK);
}

void RR_scheduling(int quantum) {
  struct PCB_st *PCB = NULL;

  while (Head != NULL) {
    PCB = Head;
    Head = Head->next;
    PCB->next = NULL;
    
    // Context switching
    for (int i = 0; i < 8; i++) {
      CPUreg[i] = PCB->myReg[i];
    }

    // Work done on the CPU
    for (int i = 0; i < quantum; i++) {
      for (int j = 0; j < 8; j++) {
        CPUreg[j]++;
      }

      CLOCK++;
    }

    // Copying CPU registers into PCB
    for (int i = 0; i < 8; i++) {
      PCB->myReg[i] = CPUreg[i];
    }

    // Checks whether process is completed or if it needs more CPU time
    if (PCB->CPUburst <= quantum) {
      PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
      Total_waiting_time = Total_waiting_time + PCB->waitingTime;
      CLOCK = CLOCK + PCB->CPUburst;
      Total_turnaround_time = Total_turnaround_time + CLOCK;
      Total_job = Total_job + 1;
      free(PCB);
    }
    else {
      PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
      CLOCK = CLOCK + quantum;
      PCB->CPUburst = PCB->CPUburst - quantum;
      PCB->queueEnterClock = CLOCK;

      // Inserts this PCB back at the end of the linked list
      if (Head == NULL) {
        Head = PCB;
      }
      else {
        Tail->next = PCB;
      }

      Tail = PCB;
    }

  }

  // Printing performance metrics
  printf("Average Waiting time = %.2f ms\t(%d/%d)\n", (float)Total_waiting_time/Total_job, waitingTime, Total_job);
  printf("Average turnaround time = %.2f ms\t(%d/%d)\n", (float)Total_turnaround_time/Total_job, Total_turnaround_time, Total_job);
  printf("Throughput = %.2f jobs per ms\t(%d/%d)\n", (float)Total_job/CLOCK, Total_job, CLOCK);
}

int main(int argc, char const *argv[]) {
  char* file = NULL;
  char* alg = NULL;
  int quantum = 0;

  // Checks the command arguments
  if (argc < 3) {
    fprintf(stderr, "Usage: %s -alg [FIFO|SJF|PR|RR] -input [input_file_name.txt]\n", argv[0]);
    return 1;
  }

  // Matches each command argument with the appropriate parameter
  for (int i = 1; i < argc; i++) {
    if ((strcmp(argv[i]), "-alg") == 0 && (i+1 < argc)) {
      alg = argv[i+1];
    }
    else if ((strcmp(argv[i]), "-input") == 0 && (i+1 < argc)) {
      file = argv[i+1];
    }
    else if ((strcmp(argv[i]), "-quantum") == 0 && (i+1 < argc)) {
      quantum = atoi(argv[i+1]);
    }
  }
  

  // Opens the file
  char *fp;
  fp = fopen(file, "r");
  if (fp == NULL) {
    perror(file);
    return 1;
  }

  // Reads the input file
  int id, pr, burst;
  while (fscanf(fp, "%d %d %d", &id, &pr, &burst) != EOF) {
    // Create a new PCB struct
    struct PCB_st *PCB = (struct PCB_st*) malloc(sizeof(struct PCB_st));

    // Saving data into PCB
    PCB->ProcId = id;
    PCB->ProcPR = pr;
    PCB->CPUburst = burst;
    for (int i = 0; i < 8; i++){
      PCB->myReg[i] = id;
    }
    PCB->queueEnterClock = 0;
    PCB->waitingTime = 0;
    PCB->next = NULL;

    // Inserting PCB at end of linked list
    if (Head == NULL) {
      Head = PCB;
      Tail = PCB;
    }
    else {
      Tail->next = PCB;
      Tail = PCB;
    }
  }

  // Prints the following lines
  printf("Student Name: Hassan Sheikh\n");
  printf("Input File Name : %s", fp);
  printf("CPU Scheduling Alg : %s", alg);

  for (int i = 0; i < Total_job; i++) {
    printf("Process %d is completed at %d ms\n", i, queueEnterClock);
  }

  // Runs each scheduling algorithm based on the -alg tag in command line
  if (strcmp(alg, "FIFO") == 0) {
    FIFO_scheduling();
  }
  else if (strcmp(alg, "SJF") == 0) {
    SJF_scheduling();
  }
  else if (strcmp(alg, "PR") == 0) {
    PR_scheduling();
  }
  else if (strcmp(alg, "RR") == 0){
    RR_scheduling();
  }


  // Closes the input file
  fclose(fp);
  
  return 0;
}