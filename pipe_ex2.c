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

Exercice 2
On souhaite écrire un programme: my-pipe cmd1 [liste d'arguments] -- cmd2 [list d'arguments] qui effectue l’équivalent de la commande shell |.

Il s’agit ici d’utiliser un tube pour relier la sortie de la commande cmd1 à l’entrée de la commande cmd2.

Tester votre programme avec mypipe ls -- wc -l (équivalent de ls | wc -l).

Faire en sorte que la commande my-pipe retourne la valeur de sortie de la première commande lorsque celle-ci n’est pas nulle et celle de la seconde autrement.

Prendre en compte la terminaison anticipée de cmd2. Tester votre programme avec mypipe dmesg -- more en appuyant sur la touche q pour quitter le programme more.

Remarque: Vous pouvez devez utiliser un appel-système de la famille exec, mais pas system.



*/
int main(int argc, char *argv[]) {

	int indice_cmd1 = 1;

	int indice_cmd2;

	for(int i= 0; i < argc; i++) {
		fprintf(stdout, "argv[%d] = %s\n", i, argv[i]);
		if (*argv[i] == '-' && *(argv[i]+1) == '-') {
			indice_cmd2 = i + 1;
			fprintf(stdout, "(pipe)\n");
		}
	}

    int pipefd[2];
    pid_t pid;
    
    if (argc < 4) {
        fprintf(stderr, "Usage: my-pipe cmd1 [liste d'arguments] -- cmd2 [list d'arguments]\n");
        exit(EXIT_FAILURE);
    }

	// Création du pipe
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe fail : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
	
	if (pid == 0) {
		// fils
        close(pipefd[0]); // on a pas besoin de l'entrée
        dup2(pipefd[1], STDOUT_FILENO); // redirection stdout to pipe
		/*
		lorsque l'on ecrira sur la sortie standard on ecrira en réalité sur pipefd[1]
		*/
		// dup2 copie le file descripteur de pipefd mais en utilisant le nombre du file descipteur 1 (stdout)
		//////////// MAN DUP /////////////////
		/*

		int dup(int oldfd);
		int dup2(int oldfd, int newfd);
		
		DESCRIPTION
       The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.

       After  a successful return, the old and new file descriptors may be used interchangeably.  They refer to the same open file description (see open(2)) and thus
       share file offset and file status flags; for example, if the file offset is modified by using lseek(2) on one of the file  descriptors,  the  offset  is  also
       changed for the other.

       The two file descriptors do not share file descriptor flags (the close-on-exec flag).  The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate de‐
       scriptor is off.

   dup2()
       The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the  file  descriptor  number
       specified in newfd.  If the file descriptor newfd was previously open, it is silently closed before being reused.

       The  steps of closing and reusing the file descriptor newfd are performed atomically.  This is important, because trying to implement equivalent functionality
       using close(2) and dup() would be subject to race conditions, whereby newfd might be reused between the two steps.  Such reuse could happen because  the  main
       program is interrupted by a signal handler that allocates a file descriptor, or because a parallel thread allocates a file descriptor.

       Note the following points:

       *  If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.

       *  If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.


		
		*/
        close(pipefd[1]); // Je ne sais pas 
        execvp(argv[indice_cmd1], NULL); // on execute la commande 1
		/*
		
		int execvp(const char *file, char *const argv[]);
		le second argument est un pointeur vers un tableau de string qui représente les paramètres à passer à notre cmd/programme

		*/
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
		// père
		close(pipefd[1]); // On utilise le pipe uniquement sur la voie de lecture
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) {
			// fils 2
			dup2(pipefd[0], STDIN_FILENO); // Redirection stdin to pipe
			/*
			
			Quand on va vouloir lire sur l'entrée standard on lira sur le pipe
			
			*/
			close(pipefd[0]);
			execvp(argv[indice_cmd2], &argv[indice_cmd2]); // Execute cmd2
			perror("execvp");
			exit(EXIT_FAILURE);
		} else {

			close(pipefd[0]);
			close(pipefd[1]); 

			int status;
			waitpid(pid, &status, 0); // fils 2

			if (WIFEXITED(status)) {
				return WEXITSTATUS(status);
			} else {
				return EXIT_FAILURE;
			}
		}
	}
}
