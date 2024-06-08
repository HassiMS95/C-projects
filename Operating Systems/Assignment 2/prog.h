#define PROG_H

// PCB Struct
struct PCB_st
{
  int ProcId;
  int ProcPR;
  int CPUburst;
  int myReg[8];
  int queueEnterClock;
  int waitingTime;
  struct PCB_st *next;
};

// CPU with 8 integer registers
int CPUreg[8] = {0};

// Linked list variables
struct PCB_st *Head = NULL;
struct PCB_st *Tail = NULL;

// Other data variables
int CLOCK = 0;
int Total_waiting_time = 0;
int Total_turnaround_time = 0;
int Total_job = 0;