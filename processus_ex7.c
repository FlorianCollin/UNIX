#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

/*

// EXERCICE 7 //

Écrire un programme qui crée un zombie. 
Le zombie devra être observable, du moins un certain temps (par ps par exemple).

*/

int main(int argc, char *argv[])
{
	pid_t fpid = fork();
	if (fpid == -1) {
		perror(" fork fail !");
		return(EXIT_FAILURE);
	}

	if (fpid == 0) {
		printf("Je suis %d et mon père est %d \n", getpid(), getppid());
		exit(EXIT_SUCCESS);
	}

	printf("Je suis le père : %d \n", getpid());


	

	return EXIT_SUCCESS;
}
