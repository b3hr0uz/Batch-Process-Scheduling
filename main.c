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
    
}*table = NULL;

typedef struct node table_type;

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
    // allocate memory for table to hold process parameters
    // for each auto-numbered process (starting from 0):
        // prompt for arrival time, and total cycle time
    // print contents of table
    return;
}
        

//*************************************************************
void option2(void) {
    // declare (and initilize when appropriate) local variables
    // for each process, reset "done" field to 0
    // while there are still processes to schedule
        // initilize the earliest arrival time to INT_MAX (largest integer value)
        // for each process not yet scheduled
            // check if process has earlier arrival time than current earliest and update
        // set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time
        // update current cycle time and increment number of processes scheduled
    // print contents of table
    return;
}


//*************************************************************
void option3(void) {
    // declare (and initilize when appropriate) local variables
    // for each process, reset "done" field to 0
    // while there are still processes to schedule
        // initilize the lowest total cycle time to INT_MAX (largest integer value)
        // for each process not yet scheduled
            // check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
        // set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
        // update current cycle time and increment number of processes scheduled
    // print contents of table
    return;
}
            

//*************************************************************
void option4(void) {
    // declare (and initilize when appropriate) local variables
    // for each process, reset "done", "total_remaining" and "already_started" fields to 0
    // while there are still processes to schedule
        // initilize the lowest total remaining time to INT_MAX (largest integer value)
        // for each process not yet scheduled
            // check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update
        // check if process already partially-scheduled
            // if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time
        // set end time, turnaround time of process with lowest (and available) total remaining cycle time
        // decrement total remaining time of process with lowest (and available) total remaining cycle time
        // if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes
    // print contents of table
    return;
}
            

//*************************************************************
void option5(void) {
    // free the schedule table if not NULL
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
