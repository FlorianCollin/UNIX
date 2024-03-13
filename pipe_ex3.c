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
Exercice 3
On souhaite disposer d’une commande log grâce à laquelle on pourrait exécuter un programme quelconque en récupérant automatiquement une copie de sa sortie standard dans un fichier. 
En quelque sorte, il s’agit de dédoubler chacun des caractères envoyés sur sa sortie standard : un exemplaire est reproduit sur la sortie standard par défaut alors que l’autre est enregistré dans un fichier.

Le programme log prend en premier argument le nom du fichier à utiliser pour la sortie. Les arguments suivants constituent la commande à exécuter :

Pour réaliser le dédoublement de la sortie standard d’un processus, une solution est de rediriger sa sortie standard vers un tube à l’extrémité duquel un second processus pourra alors facilement extraire tous les caractères et les sauver dans un fichier en même temps qu’il les affichera sur sa sortie standard.
Le programme log va donc créer un processus fils et un tube partagé par le père et le fils. Le fils, par exemple, pourra exécuter la commande spécifiée en paramètre, tandis que le père se chargera de l’affichage et de l’écriture dans le fichier. Donnez le code complet du programme log en utilisant autant que possible des fonctions d’entrée/sortie de haut niveau.

Une solution plus modulaire serait d’utiliser un programme intermédiaire (que l’on appelera tee) dont la tâche serait simplement de lire son entrée standard et de la reproduire à la fois sur la sortie standard et dans un fichier dont le nom serait passé en paramètre. Écrire tee.

$ echo Salut a tous | tee toto
Salut a tous
$ cat toto
Salut a tous

*/


/////////////////////// LOG ////////////////////////////

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
	// if (argc < 3) {
	// 	fprintf(stderr, "Usage : Le programme log prend en premier argument le nom du fichier à utiliser pour la sortie.
	// 	Les arguments suivants constituent la commande à exécuter ");
	// 	exit(EXIT_FAILURE);
	// }

	// printf("log file : %s\n", argv[1]);
	// printf("cmd : ");
	// for (int i = 2; i < argc; i++) {
	// 	printf("%s ", argv[i]);
	// }
	// printf("\n");

	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}	

	// printf("Pipe : pipedf\n");
	// printf("pipefd[0] = %d\n", pipefd[0]);
	// printf("pipedf[1] = %d\n", pipefd[1]);


	int fpid = fork();
	if (fpid == -1) {
		perror("fork");
	}

	if (fpid == 0) {
		// fils 1
 		close(pipefd[0]); // Ferme l'extrémité de lecture du tube dans le fils

        // Redirige la sortie standard vers le tube
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Ferme l'extrémité d'écriture du tube

        // Exécute la commande spécifiée

        execvp(argv[2], &argv[2]);
        perror("execvp");
        exit(EXIT_FAILURE);

	} else {
		// père
		close(pipefd[1]);

		int fd = open(argv[1], O_WRONLY|O_CREAT, 0644);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		// lecture sur le pipe
		char buffer;
		int read_status;
		int write_status;
		read_status = read(pipefd[0], &buffer, 1);
		//printf("read_status : %d\nerrno : %s\n", read_status, strerror(errno));

		while (read_status > 0) {
			printf("%c", buffer);
			write_status = write(fd, &buffer, 1);
			if (write < 0) fprintf(stderr, "Erreur lors de l'écriture dans les logs : %s\n", strerror(errno));
			read_status = read(pipefd[0], &buffer, 1);
		}

		close(pipefd[0]);
		
		int status;
        waitpid(fpid, &status, 0);
        if (WIFEXITED(status)) {
            exit(WEXITSTATUS(status));
        } else {
            exit(EXIT_FAILURE);
        }
		
	}




	return EXIT_SUCCESS;
}
