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

// EXERCICE 9 //

Reprenez l’exercice précédent, 
mais ce recouvrement devra être effectué par un processus fils créé dans le second programme.

*/


int main(int argc, char *argv[])
{
	// pog 2

	pid_t fpid = fork();

	if (fpid == -1) {
		perror("fork fail !");
	}

	if (fpid == 0) {
		// fils

		execl("./processus_ex9", "processus_ex9", NULL); // test avec execl cette fois ci 
		perror("execl fail!");
		exit(EXIT_FAILURE);

	} else {
		// père
		int status;
		wait(&status); // rappel : bloque le processus courant jusqu'a ce que le processus fils ce termine

		// rappel : la raison de l'arret du fils est stockée dans status

		// vérifions que le procesus c'est terminé normalement

		if (WIFEXITED(status)) {
			printf("Le processus fils créer par fork c'est terminé normalement \n");
		} else {
			perror("ATTENTION : terminaison du processus fils anormal !!\n");
			exit(EXIT_FAILURE);
		}
		printf("Fin du programme 2 atteint car le recouvrement est réaliser dans le processus fils !\n");
	
	}

	return EXIT_SUCCESS;
}
