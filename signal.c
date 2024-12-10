#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t flag = 0; // Global flag for signal handling
time_t start_time; // To track start time
int alarm_count = 0; // To count number of alarms

void alarm_handler(int signum) {
    printf("Hello World!\n");
    alarm(5); // Schedule next alarm in 5 seconds
    alarm_count++; // Increment alarm count
    flag = 1; // Set flag to indicate handler was invoked
}

void sigint_handler(int signum) {
    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);
    printf("Total execution time: %.f seconds\n", elapsed);
    printf("Total alarms received: %d\n", alarm_count);
    exit(0); // Exit program on CTRL-C
}

int main(int argc, char *argv[]) {
    signal(SIGALRM, alarm_handler); // Register handler for SIGALRM
    signal(SIGINT, sigint_handler); // Register handler for SIGINT (CTRL-C)

    start_time = time(NULL); // Record start time
    alarm(5); // Schedule first SIGALRM

    while (1) {
        pause(); // Wait for signals
        if (flag) { 
            printf("Turing was right!\n");
            flag = 0; // Reset flag after printing
        }
    }
    
    return 0; // This line will never be reached
}