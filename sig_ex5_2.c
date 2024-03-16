#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int signal) {
    switch(signal) {
        case SIGUSR1:
            printf(".\n");
            break;
        case SIGUSR2:
            printf("-\n");
            break;
        case SIGALRM:
            printf(" \n");
            break;
        case SIGINT:
            printf("[over]\n");
            exit(0);
            break;
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Erreur lors de la configuration du gestionnaire SIGUSR1");
        return 1;
    }

    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Erreur lors de la configuration du gestionnaire SIGUSR2");
        return 1;
    }

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Erreur lors de la configuration du gestionnaire SIGALRM");
        return 1;
    }

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de la configuration du gestionnaire SIGINT");
        return 1;
    }

    while(1) {
        sleep(1);
    }

    return 0;
}
