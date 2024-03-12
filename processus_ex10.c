#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


#include "utils.h"

#define CLOSE_OPT 1

/*

// EXERCICE 10 //

Écrivez un programme qui ouvre un fichier quelconque et qui affiche la valeur de l’index de descripteur associé.
Exécutez ce programme directement en le lançant depuis un terminal puis de nouveau en créant un processus fils qui fait un exec de ce même programme. Que constatez-vous?
*/


int main(int argc, char *argv[])
{
	int fd = open("./file.txt", O_RDONLY, 0);
	if (fd < 0) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Descripteur de fichier : %d \n", fd);

	// il faut penser à liberer la table des descripteur

	if (CLOSE_OPT) {
		if (close(fd) != 0) {
			fprintf(stderr,"Erreur lors de la fermeture du fichier : %s\n", strerror(errno));
		}
	}

	return EXIT_SUCCESS;
}
