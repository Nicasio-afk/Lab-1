#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("Hello World!\n");
    alarm(5); // Reschedule the alarm
}

int main() {
    signal(SIGALRM, handler); // Register handler to handle SIGALRM
    alarm(5); // Schedule a SIGALRM for 5 seconds
    while (1) {
        pause(); // Wait for signals
        printf("Turing was right!\n");
    }
    return 0;
}
