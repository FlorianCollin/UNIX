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
Écrire une commande emettre-signaux pid-cible k s1 s2 ... sn qui émet à destination du processus cible k fois la séquence de signaux donnée en paramètre.

Utiliser cette commande pour “bombarder” de signaux un processus exécutant la commande de l’exercice précédent.

*/


int main(int argc, char *argv[])
{
	printf("Hello world \n");
	printf("My PID : %d\n", getpid());

	if (argc < 3) {
		fprintf(stderr, "Usage : emettre-signaux pid-cible k s1 s2 ... sn\n");
		exit(EXIT_FAILURE);
	}

	int pid_cible = atoi(argv[1]);
	int k = atoi(argv[2]);
	int s = atoi(argv[3]);

	printf("pid-cible : %d\n", pid_cible);
	printf("k         : %d\n", k);
	printf("signal    : %d\n", s);

	for (int i = 0; i < k; i++) {
		if (kill(pid_cible, s) == -1) {
			perror("kill fail !");
			exit(EXIT_FAILURE);
		}
		sleep(1);
	}

	return EXIT_SUCCESS;
}
