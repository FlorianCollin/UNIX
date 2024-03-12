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

// EXERCICE 2 //

Écrivez un programme qui redirige tous ses printf dans un fichier output.txt plutôt que sur sa sortie standard (sans modifier les appels à printf dans le programme).

*/



int main(int argc, char *argv[])
{

	printf("File descriptor STDOUT_FILENO : %d\n", STDOUT_FILENO);
	// Fermeture de STDIN_FILENO

	if (close(STDOUT_FILENO) != 0) {
		fprintf(stderr, "Erreur lors de la fermeture de STDOUT_FILENO : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	int fd = open("./output.txt", O_WRONLY|O_CREAT, S_IRWXU);

	if (fd < 0) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Hello world\n"); // on ecrit sur fd = 1 or 1 est associé à "output.txt"


	if (close(fd) != 0) {
		fprintf(stderr,"Erreur lors de la fermeture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	return EXIT_SUCCESS;
}
