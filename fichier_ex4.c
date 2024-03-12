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
	int fd = open("./file.txt", O_RDONLY, 0);
	if (fd < 0) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Descripteur de fichier : %d \n", fd);


	pid_t fpid = fork(); // duplication de la table des descripteur 

	if (fpid < 0) {
		perror("fork fail !\n");
		exit(EXIT_FAILURE);
	}

	if (fpid == 0){
		/*
		On va utiliser execl or l'appel a exec ne ferme pas les descripteur ainsi on ouvrira deux entrées dans la table des descripteurs,
		puis 3 puis 4 ...
		*/
		execl("./fichier_ex4", "fichier_ex4", NULL);
		perror("execl fail !\n");
		return EXIT_FAILURE;
	} else {
		wait(NULL);
	}

	if (close(fd) != 0) {
		fprintf(stderr,"Erreur lors de la fermeture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	return EXIT_SUCCESS;
}

/*
...
Descripteur de fichier : 3506 
Descripteur de fichier : 3507 
Descripteur de fichier : 3508 
Descripteur de fichier : 3509 
Descripteur de fichier : 3510 
Descripteur de fichier : 3511 
Descripteur de fichier : 3512 
Descripteur de fichier : 3513 
Descripteur de fichier : 3514 
Descripteur de fichier : 3515 
Descripteur de fichier : 3516 
Descripteur de fichier : 3517 
Descripteur de fichier : 3518 
Descripteur de fichier : 3519 
Descripteur de fichier : 3520 
Descripteur de fichier : 3521 
Descripteur de fichier : 3522
...

On utilise un nouveaux descripteur à chaque fois !
*/