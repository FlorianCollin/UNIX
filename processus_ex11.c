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

// EXERCICE 11 //

Écrire une fonction int systeme(char *commande) qui lance un processus exécutant un shell pour interpréter la commande passée en paramètre 
puis attends la fin de cette interprétation pour retourner. 

Voir la fonction system.

*/

int systeme(char *commande) {
	
	pid_t fpid = fork();

	if (fpid == -1) {
		perror("fork fail !\n");
		exit(EXIT_FAILURE);
	}

	if (fpid == 0) {
		// fils

		printf("Je suis le processus fils : %d et mon père est : %d\n", getpid(), getppid());
		execlp("/bin/sh", "sh", "-c", commande, (char *)NULL); // man system page
		perror("execlp fail!\n");
		exit(EXIT_FAILURE);
	} else {
		// père
		printf("Je suis le processus père : %d\n", getpid());
		int status;
		wait(&status);

		if (WIFEXITED(status) > 0) {
			printf("Le processus fils c'est bien terminé\n");
		} else {
			perror("ATTENTION : terminaison du processus fils anormal !!\n");
			exit(EXIT_FAILURE);
		}
	}		

}

int main(int argc, char *argv[])
{
	int exit_status = systeme("ls");

	if (exit_status == EXIT_FAILURE) {
		printf("Echec de la commande systeme\n");
		return EXIT_FAILURE;
	} else {
		printf("OK!\n");
		return EXIT_SUCCESS;
	}
	
}
