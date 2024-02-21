//
//  main.c
//  Batch-Process-Scheduling
//
//  Created by Behrouz Barati on 2/20/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// declare global variables including a table structure to hold scheduling information
struct node {
    int id;
    int done;
    int arrival;
    int startTime;
    int endTime;
    int totalCPUTime;
    int turnaroundTime;
    int totalCycleTime;
    int totalRemainingTime;
    int alreadyStarted;
    
}*table = NULL;

typedef struct node table_type;

int numberOfProcesses;

// optional: define a function that finds the maximum of two integers
#define max(a,b) (a>b ? a : b)

//***************************************************************
void printSchedulingTable(void) {
    // declare local variables
    // print table header
    // for each process
        // print the contents (id, arrival time, total_cycles) of each field of the table's index
        // if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time)
    return;
}


//*************************************************************
void option1(void) {
    // declare local variables

    // prompt for total number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &numberOfProcesses);

    // allocate memory for table to hold process parameters
    table = (table_type *)malloc(numberOfProcesses * sizeof(table_type));
    // for each auto-numbered process (starting from 0):
    for (int i = 0; i < numberOfProcesses; i++) {
        // prompt for arrival time, and total cycle time
        printf("Enter arrival cycle for process %d: ", i);
        scanf("%d", &table[i].arrival);
        printf("\nEnter total cycle time for process %d: ", i);
        scanf("%d", &table[i].totalCycleTime);
        table[i].id = i;
    }
        
    // print contents of table
    printSchedulingTable();
    
    return;
}
        

//*************************************************************
void FIFO(void) {
    // declare (and initilize when appropriate) local variables
    int numberOfProcessesDone = 0;
    int earliestTime;
    int minArrivalTimeIndex = 0;
    int currentCycle = 0;
    
    // for each process, reset "done" field to 0
    for (int i = 0; i < numberOfProcesses; i++) table[i].done = 0;
        
    // while there are still processes to schedule
    while (numberOfProcessesDone < numberOfProcesses){
        // initilize the earliest arrival time to INT_MAX (largest integer value)
        earliestTime = INT_MAX;
        // for each process not yet scheduled
        for (int i = 0; i < numberOfProcesses; i++) {
            if (table[i].done == 0) {
                // check if process has earlier arrival time than current earliest and update
                if (table[i].arrival < earliestTime) {
                    earliestTime = table[i].arrival;
                    minArrivalTimeIndex = i;
                }
            }
        }
        
        // set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time
        table[minArrivalTimeIndex].startTime = max(table[minArrivalTimeIndex].arrival, currentCycle);
        table[minArrivalTimeIndex].endTime = table[minArrivalTimeIndex].startTime + table[minArrivalTimeIndex].totalCPUTime;
        table[minArrivalTimeIndex].turnaroundTime = table[minArrivalTimeIndex].endTime - table[minArrivalTimeIndex].arrival;
        // update current cycle time and increment number of processes scheduled
        currentCycle = table[minArrivalTimeIndex].endTime;
        numberOfProcessesDone++;
        table[minArrivalTimeIndex].done = 1;
    }
    
    // print contents of table
    printSchedulingTable();
    
    return;
}


//*************************************************************
void SJF(void) {
    // we can do it another way, first we sort processes with totalCPUTime
    
    // declare (and initilize when appropriate) local variables
    int numberOfProcessesDone = 0;
    int lowestCycle;
    int minArrivalTimeIndex = 0;
    int currentCycle = 0;
    int atLeastOne;
    
    // for each process, reset "done" field to 0
    for (int i = 0; i < numberOfProcesses; i++) table[i].done = 0;
    
    // while there are still processes to schedule
    while (numberOfProcessesDone < numberOfProcesses){
        // initilize the lowest total cycle time to INT_MAX (largest integer value)
        lowestCycle = INT_MAX;
        atLeastOne = 0;
        
        // for each process not yet scheduled
        for (int i = 0; i < numberOfProcesses; i++) {
            if (table[i].done == 0) {
                // check if process has earlier arrival time than current earliest and update
                if ((table[i].totalCPUTime < lowestCycle) && (table[i].arrival <= currentCycle)) {
                    lowestCycle = table[i].totalCPUTime;
                    minArrivalTimeIndex = i;
                    // one more thing we gotta do
                    atLeastOne = 1;
                }
            }
        }

        // check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
        if (atLeastOne == 1){
            // set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
            table[minArrivalTimeIndex].startTime = max(table[minArrivalTimeIndex].arrival, currentCycle);
            table[minArrivalTimeIndex].endTime = table[minArrivalTimeIndex].startTime + table[minArrivalTimeIndex].totalCPUTime;
            table[minArrivalTimeIndex].turnaroundTime = table[minArrivalTimeIndex].endTime - table[minArrivalTimeIndex].arrival;
            // update current cycle time and increment number of processes scheduled
            currentCycle = table[minArrivalTimeIndex].endTime;
            numberOfProcessesDone++;
            table[minArrivalTimeIndex].done = 1;
        }
        // update current cycle time and increment number of processes scheduled
        else currentCycle++;
    }
    
    // print contents of table
    printSchedulingTable();
    
    return;
}
            

//*************************************************************
void SRT(void) {
    // declare (and initilize when appropriate) local variables
    int numberOfProcessesDone = 0;
    int lowestTotalRemainingTime;
    int minArrivalTimeIndex = 0;
    int currentCycle = 0;
    int atLeastOne;
    
    // for each process, reset "done", "total_remaining" and "already_started" fields to 0
    for (int i = 0; i < numberOfProcesses; i++){
        table[i].done = 0;
        table[i].alreadyStarted = 0;
        table[i].totalRemainingTime = table[i].totalCPUTime;
    }
    
    // while there are still processes to schedule
    while (numberOfProcessesDone < numberOfProcesses){
        // initilize the lowest total remaining time to INT_MAX (largest integer value)
        lowestTotalRemainingTime = INT_MAX;
        atLeastOne = 0;
        
        // for each process not yet scheduled
        for (int i = 0; i < numberOfProcesses; i++) {
            if (table[i].done == 0) {
                // check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update
                if ((table[i].totalRemainingTime < lowestTotalRemainingTime) && (table[i].arrival <= currentCycle)) {
                    lowestTotalRemainingTime = table[i].totalCPUTime;
                    minArrivalTimeIndex = i;
                    // one more thing we gotta do
                    atLeastOne = 1;
                }
            }
        }
            // check if process already partially-scheduled
            if (atLeastOne == 1){
                // set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
                if (table[minArrivalTimeIndex].alreadyStarted ==0) {
                    // if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time
                    table[minArrivalTimeIndex].startTime = max(table[minArrivalTimeIndex].arrival, currentCycle);
                    table[minArrivalTimeIndex].alreadyStarted = 1;
                }//if not already started
                
                // set end time, turnaround time of process with lowest (and available) total remaining cycle time
                    table[minArrivalTimeIndex].endTime = currentCycle + 1;
                    table[minArrivalTimeIndex].turnaroundTime = table[minArrivalTimeIndex].endTime - table[minArrivalTimeIndex].arrival;
                // decrement total remaining time of process with lowest (and available) total remaining cycle time
                table[minArrivalTimeIndex].totalRemainingTime--;
                // if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes
                if (table[minArrivalTimeIndex].totalRemainingTime == 0) {
                    table[minArrivalTimeIndex].done = 1;
                    numberOfProcessesDone++;
                }// if process is done
            }
            
            // update current cycle time and increment number of processes scheduled
            currentCycle++;
        }
    
    // print contents of table
    printSchedulingTable();
    
    return;
}
            

//*************************************************************
void option5(void) {
    // free the schedule table if not NULL
    if (table != NULL) free(table);

    return;
}


//*************************************************************
int main(void) {
    /*// declare local vars
    // while user has not chosen to quit
        // print menu of options
        // prompt for menu selection
        // call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
    } // while loop*/
     return 1; // indicates success
} // end of procedure
