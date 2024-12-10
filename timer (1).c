#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int alarm_count = 0; // Counter for the number of alarms
time_t start_time;   // Variable to track the start time

// Signal handler for SIGALRM
void alarm_handler(int signum){
    alarm_count++;  // Increment the alarm count
    alarm(1);      // Schedule the next alarm in 1 second
}

// Signal handler for SIGINT (CTRL-C)
void exit_handler(int signum){
    time_t end_time = time(NULL); // Get the current time
    int elapsed_seconds = end_time - start_time; // Calculate elapsed time
    printf("Total execution time: %d seconds\n", elapsed_seconds);
    printf("Number of alarms: %d\n", alarm_count);
    exit(0); // Exit the program
}

int main(int argc, char *argv[]){
    start_time = time(NULL); // Record the start time

    struct sigaction sa;
    
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    sa.sa_handler = exit_handler;
    sigaction(SIGINT, &sa, NULL);

    alarm(1); // Schedule the first alarm in 1 second

    while(1){
        pause(); // Wait for signals
    }
    
    return 0; // This line will never be reached
}