//
//  main.c
//  Batch-Process-Scheduling
//
//  Created by Behrouz Barati on 2/20/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Declare global variables including a table structure to hold scheduling information
struct node {
    int id;
    int done;
    int arrival;
    int startTime;
    int endTime;
    int totalCPUTime;
    int turnaroundTime;
    int totalRemainingTime;
    int alreadyStarted;
}*table = NULL;
typedef struct node table_type;

int numberOfProcesses;

// Optional: define a function that finds the maximum of two integers
#define max(a,b) (a>b ? a : b)

//***************************************************************
void printSchedulingTable(void) {
    // Declare local variables
    
    // Print table header
    printf("\nPID\tArrival\tTotal\tStart\tEnd\t\tTurnaround\tDone\n");
    printf("-----------------------------------------------------\n");
    // For each process
    for (int i = 0; i < numberOfProcesses; i++) {
        // Print the contents (id, arrival time, total_cycles) of each field of the table's index
        printf("%d\t%d\t\t%d\t\t", table[i].id, table[i].arrival, table[i].totalCPUTime);
        // If process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time)
        if (table[i].done) { // Only print the rest if the process is done
            printf("%d\t\t%d\t\t%d\t\t\t%d\n", table[i].startTime, table[i].endTime, table[i].turnaroundTime, table[i].done);
        } else {
            printf("N/A\t\tN/A\t\tN/A\t\t\t%d\n", table[i].done);
        }
    }
    return;
}

//*************************************************************
void option1(void) {
    // Declare local variables

    // Prompt for total number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &numberOfProcesses);
    // Allocate memory for table to hold process parameters
    table = (table_type *)malloc(numberOfProcesses * sizeof(table_type));
    // for each auto-numbered process (starting from 0):
    for (int i = 0; i < numberOfProcesses; i++) {
        // Prompt for arrival time, and total cycle time
        printf("Enter arrival cycle for process %d: ", i);
        scanf("%d", &table[i].arrival);
        printf("Enter total cycles for process %d: ", i);
        scanf("%d", &table[i].totalCPUTime);
        // Properly initialize all required fields for the new logic
        table[i].id = i;
        table[i].done = 0;
        table[i].totalRemainingTime = table[i].totalCPUTime; // Necessary for SRT logic
        table[i].alreadyStarted = 0; // Necessary for SRT logic
        // No need to initialize start, end, and turnaround times here as they will be set during scheduling
    }
    // Print contents of table after initialization
    printSchedulingTable();
    return;
}
        
//*************************************************************
void FIFO(void) {
    // Declare (and initilize when appropriate) local variables
    int numberOfProcessesDone = 0;
    int earliestTime;
    int minArrivalTimeIndex = 0;
    int currentCycle = 0;
    // For each process, reset "done" field to 0
    for (int i = 0; i < numberOfProcesses; i++) table[i].done = 0;
    // While there are still processes to schedule
    while (numberOfProcessesDone < numberOfProcesses){
        // Initilize the earliest arrival time to INT_MAX (largest integer value)
        earliestTime = INT_MAX;
        // For each process not yet scheduled
        for (int i = 0; i < numberOfProcesses; i++) {
            if (table[i].done == 0) {
                // Check if process has earlier arrival time than current earliest and update
                if (table[i].arrival < earliestTime) {
                    earliestTime = table[i].arrival;
                    minArrivalTimeIndex = i;
                }
            }
        }
        // Set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time
        table[minArrivalTimeIndex].startTime = max(table[minArrivalTimeIndex].arrival, currentCycle);
        table[minArrivalTimeIndex].endTime = table[minArrivalTimeIndex].startTime + table[minArrivalTimeIndex].totalCPUTime;
        table[minArrivalTimeIndex].turnaroundTime = table[minArrivalTimeIndex].endTime - table[minArrivalTimeIndex].arrival;
        // Update current cycle time and increment number of processes scheduled
        currentCycle = table[minArrivalTimeIndex].endTime;
        numberOfProcessesDone++;
        table[minArrivalTimeIndex].done = 1;
    }
    // Print contents of table
    printSchedulingTable();
    return;
}

//*************************************************************
void SJF(void) {
    // We can do it another way: we sort processes with totalCPUTime first.
    // Declare (and initilize when appropriate) local variables
    int numberOfProcessesDone = 0;
    int lowestCycle;
    int minArrivalTimeIndex = 0;
    int currentCycle = 0;
    int atLeastOne;
    // For each process, reset "done" field to 0
    for (int i = 0; i < numberOfProcesses; i++) table[i].done = 0;
    // While there are still processes to schedule
    while (numberOfProcessesDone < numberOfProcesses){
        // Initilize the lowest total cycle time to INT_MAX (largest integer value)
        lowestCycle = INT_MAX;
        atLeastOne = 0;
        // For each process not yet scheduled
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
        // Check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
        if (atLeastOne == 1){
            // Set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
            table[minArrivalTimeIndex].startTime = max(table[minArrivalTimeIndex].arrival, currentCycle);
            table[minArrivalTimeIndex].endTime = table[minArrivalTimeIndex].startTime + table[minArrivalTimeIndex].totalCPUTime;
            table[minArrivalTimeIndex].turnaroundTime = table[minArrivalTimeIndex].endTime - table[minArrivalTimeIndex].arrival;
            // Update current cycle time and increment number of processes scheduled
            currentCycle = table[minArrivalTimeIndex].endTime;
            numberOfProcessesDone++;
            table[minArrivalTimeIndex].done = 1;
        }
        // Update current cycle time and increment number of processes scheduled
        else currentCycle++;
    }
    // Print contents of table
    printSchedulingTable();
    return;
}
            
//*************************************************************
void SRT(void) {
    // Declare (and initialize when appropriate) local variables
    int numberOfProcessesDone = 0;
    int lowestTotalRemainingTime;
    int minArrivalTimeIndex = -1;
    int currentCycle = 0;
    int atLeastOne;
    // For each process, reset "done", "total_remaining" and "already_started" fields to 0
    for (int i = 0; i < numberOfProcesses; i++){
        table[i].done = 0;
        table[i].alreadyStarted = 0;
        table[i].totalRemainingTime = table[i].totalCPUTime;
    }
    // While there are still processes to schedule
    while (numberOfProcessesDone < numberOfProcesses){
        // initialize the lowest total remaining time to INT_MAX (largest integer value)
        lowestTotalRemainingTime = INT_MAX;
        atLeastOne = 0;
        // For each process not yet scheduled
        for (int i = 0; i < numberOfProcesses; i++) {
            if (table[i].done == 0 && table[i].arrival <= currentCycle) {
                // check if process has lower total remaining time than current lowest and update
                if (table[i].totalRemainingTime < lowestTotalRemainingTime) {
                    lowestTotalRemainingTime = table[i].totalRemainingTime;
                    minArrivalTimeIndex = i;
                    atLeastOne = 1;
                }
            }
        }
        // Check if process already partially-scheduled
        if (atLeastOne == 1){
            // If not already started
            if (table[minArrivalTimeIndex].alreadyStarted == 0) {
                // Set "start time" and "already_started" fields of process with lowest (and available) total remaining cycle time
                table[minArrivalTimeIndex].startTime = currentCycle;
                table[minArrivalTimeIndex].alreadyStarted = 1;
            }
            // Process for one cycle
            table[minArrivalTimeIndex].totalRemainingTime--;
            currentCycle++; // Increment current cycle
            // If remaining time is 0, set done field to 1, and update process completion info
            if (table[minArrivalTimeIndex].totalRemainingTime == 0) {
                table[minArrivalTimeIndex].done = 1;
                table[minArrivalTimeIndex].endTime = currentCycle; // set end time
                table[minArrivalTimeIndex].turnaroundTime = table[minArrivalTimeIndex].endTime - table[minArrivalTimeIndex].arrival;
                numberOfProcessesDone++;
            }
        } else {
            // No process is ready; increment the cycle
            currentCycle++;
        }
    }
    // Print contents of table
    printSchedulingTable();
    return;
}

//*************************************************************
void option5(void) {
    // Free the schedule table if not NULL
    if (table != NULL) {
        free(table);
        table = NULL;
    }
    printf("Quitting program...\n");
    return;
}

//*************************************************************
int main(void) {
    // Declare local vars
     int choice;
    // While user has not chosen to quit
    do {
        // Print menu of options
        printf("Batch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");
        // Prompt for menu selection
        printf("Enter selection: ");
        scanf("%d", &choice);
        // Call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
        switch(choice) {
            case 1:
                option1();
                break;
            case 2:
                FIFO(); // Call FIFO scheduling function.
                break;
            case 3:
                SJF(); // Call SJF scheduling function.
                break;
            case 4:
                SRT(); // Call SRT scheduling function.
                break;
            case 5:
                option5(); // Clean up and exit.
                break;
            default:
            printf("Invalid option. Please try again.\n");
        }
    } while(choice != 5); // Loop until the user selects option 5. // while loop
     return 0; // Indicates success
} // End of procedure
