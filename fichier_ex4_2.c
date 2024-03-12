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
	// pid_t fpid = fork();
	// if (fpid == -1) {
	// 	perror("fork fail !\n");
	// 	exit(EXIT_FAILURE);
	// }

	// if (fpid == 0){
	// 	execl("./fichier_ex4", "fichier_ex4", NULL);
	// 	perror("execl fail !\n");
	// 	return EXIT_FAILURE;
	// } else {
	// 	int status;
	// 	wait(&status);
	// 	if(WIFEXITED(status) > 0) {
	// 		printf("processus fils terminé normalement !\n,");
	// 	} else {
	// 		fprintf(stderr,"processus fils terminé anormalement");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }


	int fd1 = open("./file.txt", O_RDONLY, 0);
	if (fd1 < 0) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Descripteur de fichier fd1 : %d \n", fd1);

		int fd2 = open("./file.txt", O_RDONLY, 0);
	if (fd2 < 0) {
		fprintf(stderr, "Erreur d'ouverture du fichier fd2 : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Descripteur de fichier fd2 : %d \n", fd2);


}
/*

Descripteur de fichier fd1 : 3 
Descripteur de fichier fd2 : 4 

*/

