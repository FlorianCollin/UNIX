#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


#include "utils.h"


/*

// EXERCICE 10 //

Écrivez un programme qui ouvre un fichier quelconque et qui affiche la valeur de l’index de descripteur associé.
Exécutez ce programme directement en le lançant depuis un terminal puis de nouveau en créant un processus fils qui fait un exec de ce même programme. Que constatez-vous?
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

		execl("./processus_ex10", "processus_ex10", NULL);
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
