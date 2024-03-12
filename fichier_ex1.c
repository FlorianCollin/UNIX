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

// EXERCICE 1 //

Créer un fichier dans votre répertoire de travail. 
Écrivez ensuite un programme qui ouvre ce fichier et affichez la valeur (de l’index) du descripteur associé. Cette valeur est-elle conforme à vos attentes? 
Que se passe t-il si vous exécuter la commande close(STDIN_FILENO) avant l’appel de open?

*/

int main(int argc, char *argv[])
{

	printf("File descriptor STDIN_FILENO : %d\n", STDIN_FILENO);
	// Fermeture de STDIN_FILENO

	close(STDIN_FILENO);

	int fd = open("./file.txt", O_RDONLY, 0);
	if (fd < 0) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Descripteur de fichier : %d \n", fd);

	// Il faut penser à liberer la table des descripteur


	if (close(fd) != 0) {
		fprintf(stderr,"Erreur lors de la fermeture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	return EXIT_SUCCESS;
}


/*

File descriptor STDIN_FILENO : 2
Descripteur de fichier : 0 

Explicaiton :

On a fermer fd = 0 donc quand on ouvre avec open on prend la première valeur de libre soit 0 !
*/

