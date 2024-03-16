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

Excerice 1
Écrire un programme qui boucle tout en affichant ctrl-c lorsque le processus qui l’exécute reçoit le signal SIGINT.

Dans un second temps on fera en sorte que seul le premier signal SIGINT soit traité. 

*/

void handle_sigint(int sig) {
	static int sig_count = 0;
    if (sig_count == 0) {
        printf("ctrl-c\n");
    }
    if (sig_count == 1) {
        signal(SIGINT, SIG_DFL);
		printf("SIGINT function is set by default\n");
	}
	sig_count++;
}

int main(int argc, char *argv[])
{
	// SIGINT	Interruption (Ctrl-C)

	signal(SIGINT, handle_sigint);

	while (1) {
		// attente d'un Ctrl-c
	}
	

	return EXIT_SUCCESS;
}
