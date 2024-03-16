#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
Exercice 5
Cet exercice a pour but de réaliser une communication utilisant le code morse (ou un quelconque code similaire) entre deux processus — un client et un serveur — au moyen de signaux. Un résumé du codage morse est disponible dans le fichier morse.txt. Pour information, il faut y ajouter les particularités suivantes:

les signes morses sont séparés par un blanc ;
les lettres sont séparées par trois blancs ;
les mots sont séparés par sept blancs.
*/

void sigusr1_handle(int sig) {
    printf(".\n");
    // demander au prof pourquoi ca ne marche pas sans le saut de ligne
}

void sigusr2_handle(int sig) {
    printf("-\n");
}

void sigalrm_handle(int sig) {
    printf(" \n");
}

int main(int argc, char *argv[]) {
    
    printf("My PID : %d\n", getpid());
    
    // SIGUSR2

    struct sigaction sa_sigusr1;
    sa_sigusr1.sa_handler = sigusr1_handle;
    sigemptyset(&sa_sigusr1.sa_mask);
    sa_sigusr1.sa_flags = 0;
    
    if (sigaction(SIGUSR1, &sa_sigusr1, NULL) == -1 ) {
        perror("sigaction (SIGUSR0) fail !");
        exit(EXIT_FAILURE);
    }

    // SIGUSR2

    struct sigaction sa_sigusr2;
    sa_sigusr2.sa_handler = sigusr2_handle;
    sigemptyset(&sa_sigusr2.sa_mask);
    sa_sigusr2.sa_flags = 0;

    if (sigaction(SIGUSR2, &sa_sigusr2, NULL) == -1 ) {
        perror("sigaction (SIGUSR2) fail !");
        exit(EXIT_FAILURE);
    }     

    // SIGALRM

    struct sigaction sa_sigalrm;
    sa_sigalrm.sa_handler = sigalrm_handle;
    sigemptyset(&sa_sigalrm.sa_mask);
    sa_sigalrm.sa_flags = 0;

    if (sigaction(SIGALRM, &sa_sigalrm, NULL) == -1 ) {
        perror("sigaction (SIGARLRM) fail !");
        exit(EXIT_FAILURE);
    }     
    

    while (1) {
    }

    return 0;
}
