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

// EXERCICE 4 //

Écrivez un programme qui ouvre un fichier quelconque 
et qui affiche la valeur de l’index de descripteur associé.

Exécutez ce programme directement en le lançant depuis un terminal 
puis de nouveau en créant un processus fils qui fait un exec de ce même programme. 
Que constatez-vous?
*/


int main(int argc, char *argv[])
{

	int fpid = fork();

	if (fpid < 0) {
		perror("fork fail !\n");
		exit(EXIT_FAILURE);
	}
	
	if (fpid > 0) {
		//père 
		int fd3 = open("./file.txt", O_RDONLY, 0);
		if (fd3 < 0) {
			fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("Père : Descripteur de fichier fd3 : %d \n", fd3);

		

		int fd4 = open("./file.txt", O_RDONLY, 0);
		if (fd3 < 0) {
			fprintf(stderr, "Erreur d'ouverture du fichier fd3 : %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("Père : Descripteur de fichier fd4 : %d \n", fd4);

		wait(NULL);
		close(fd3);
		close(fd4);
	
		
	
	} else if (fpid == 0) {
		// fils
		int fd1 = open("./file.txt", O_RDONLY, 0);
		if (fd1 < 0) {
			fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("Fils : Descripteur de fichier fd1 : %d \n", fd1);

		int fd2 = open("./file.txt", O_RDONLY, 0);
		if (fd2 < 0) {
			fprintf(stderr, "Erreur d'ouverture du fichier fd2 : %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("Fils : Descripteur de fichier fd2 : %d \n", fd2);

		close(fd1);
		close(fd2);
	}


}

