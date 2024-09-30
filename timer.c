#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarm_count = 0;
time_t start_time;

void alarm_handler(int signum) {
    alarm_count++;
    printf("Hello World!\n");
    alarm(1); // Reschedule the alarm for every second
}

void sigint_handler(int signum) {
    time_t end_time = time(NULL);
    printf("\nTuring was right!\n");
    printf("Total execution time: %ld seconds\n", end_time - start_time);
    printf("Total alarms: %d\n", alarm_count);
    exit(0);
}

int main() {
    start_time = time(NULL);
    signal(SIGALRM, alarm_handler); // Register handler to handle SIGALRM
    signal(SIGINT, sigint_handler); // Register handler to handle SIGINT
    alarm(1); // Schedule a SIGALRM for 1 second
    while (1) {
        pause(); // Wait for signals
    }
    return 0;
}
