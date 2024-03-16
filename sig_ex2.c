#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "utils.h"

/*

Exercice 2
Écrire une commande recevoir-signaux qui affiche son pid puis boucle tout en affichant en les numérotant (dénombrant) les signaux que son processus reçoit.

Tester cette commande en utilisant la commande unix kill.

*/


void sigusr1_handle(int sig) {
	static int count = 0;
	printf("Received : SIGUSR1 (%d) \n", count);
	count++;
}


int main(int argc, char *argv[])
{
	
	printf("Hello world \n");
	printf("My PID : %d\n", getpid());

	/*
	
	struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };

	
	*/
	// création de la structure sigaction
	struct sigaction sa;
    sa.sa_handler = sigusr1_handle;
    sigemptyset(&sa.sa_mask); // aucun signal doit être bloqué quand le signal SIGUSR1 est recu
    sa.sa_flags = 0;


	/*
	int sigaction(int signum, const struct sigaction *act,
                    struct sigaction *oldact);

	*/
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Erreur lors de la configuration du gestionnaire de signal");
        exit(EXIT_FAILURE);
    }

	
	while (1) {
		// Attente de signaux
		sleep(1);
	}

	return EXIT_SUCCESS;
}
