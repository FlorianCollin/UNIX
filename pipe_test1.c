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

// EXEMPLE PIPE //

*/

#define BUFFER_SIZE 256

int main() {
    int pipefd[2]; // Descripteurs de fichier pour le tube
    pid_t pid; // Identifiant du processus

    char message[] = "Bonjour, monde !";
    char buffer[BUFFER_SIZE];

    // Création du tube
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	printf("Pipe créer, pipefd[0] = %d, pipefd[1] = %d\n", pipefd[0], pipefd[1]);

    // Création du processus fils
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Code du processus fils
        close(pipefd[1]); // Ferme l'extrémité d'écriture du tube dans le processus fils
        
        // Lecture du message du processus parent à partir du tube
        read(pipefd[0], buffer, BUFFER_SIZE);
        printf("Message reçu par le fils : %s\n", buffer);

        close(pipefd[0]); // Ferme l'extrémité de lecture du tube dans le processus fils
        exit(EXIT_SUCCESS);
    } else { // Code du processus parent
        close(pipefd[0]); // Ferme l'extrémité de lecture du tube dans le processus parent

        // Écriture du message dans le tube
        dup2(pipefd[1], STDOUT_FILENO);

        printf("%s", message);
        //write(pipefd[1], message, strlen(message) + 1);
        printf("Message envoyé par le parent : %s\n", message);



        close(pipefd[1]); // Ferme l'extrémité d'écriture du tube dans le processus parent

        // Attente de la fin du processus fils
        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}
