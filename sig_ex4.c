#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*

Exercice 4
Il s’agit maintenant de faire dialoguer un père et son fils à l’aide de signaux. 
Pour cela on va écrire une commande signaux-pere-fils k s1 s2 ... sn où le fils va émettre vers son père k fois la séquence de signaux donnée en paramètre. 
On utilisera le signal KILL pour terminer le dialogue.

Afin de ne pas perdre de signaux on va mettre en œuvre le protocole suivant : le père devra envoyer au fils le signal USR1 pour acquitter chaque réception, de son coté le fils devra attendre l’acquittement du père pour poursuivre l’émission.

*/

volatile sig_atomic_t received = 0;

void handle_sigusr1_child(int sig) {
    received = 1;
}

void handle_sigusr2_parent(int sig) {
	static int count = 0;
	printf("SIGUSR2 (%d)\n", count);
	count++;
}

void handle_sigusr1_parent(int sig) {
}

int main(int argc, char *argv[]) {
  	if (argc < 3) {
		fprintf(stderr, "Usage : signaux-pere-fils k s1 s2 ... sn\n");
		exit(EXIT_FAILURE);
	}

    int k = atoi(argv[1]);

    pid_t pid = fork();

    if (pid == -1) {
        perror("Erreur lors de la création du fils");
        exit(EXIT_FAILURE);
    } 
	
	if (pid == 0) {
		// fils
		struct sigaction sa;
		sa.sa_handler = handle_sigusr1_child;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		
        // signal(SIGUSR1, handle_sigusr1_child);
		sigaction(SIGUSR1, &sa, NULL);


		int ppid = getppid();

        for (int i = 0; i < k; i++) {
            while (!received) {
            }
            received = 0;
            for (int j = 2; j < argc; j++) {
                int signum = atoi(argv[j]);
				// Envoie des signaux au père
                if (kill(ppid, signum) == -1) {
                    perror("Erreur lors de l'envoi du signal au père");
                    exit(EXIT_FAILURE);
                }
            }
        }

		// fin de la communication entre le père et le fils.
        if (kill(ppid, SIGKILL) == -1) {
            perror("Erreur lors de l'envoi du signal SIGKILL au père");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    } else {
		struct sigaction sa_parent;
		sa_parent.sa_handler = handle_sigusr1_parent;
		sigemptyset(&sa.sa_mask);
		sa_parent.sa_flags = 0;
		
		sigaction(SIGUSR1, &sa_parent, NULL);
        // signal(SIGUSR1, handle_sigusr1_parent);

        while (1) {
        }
    }

    return 0;
}
