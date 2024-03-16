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

Exercice 4
Il s’agit maintenant de faire dialoguer un père et son fils à l’aide de signaux. Pour cela on va écrire une commande signaux-pere-fils k s1 s2 ... sn où le fils va émettre vers son père k fois la séquence de signaux donnée en paramètre. On utilisera le signal KILL pour terminer le dialogue.

Afin de ne pas perdre de signaux on va mettre en œuvre le protocole suivant : le père devra envoyer au fils le signal USR1 pour acquitter chaque réception, de son coté le fils devra attendre l’acquittement du père pour poursuivre l’émission.Exercice 4
Il s’agit maintenant de faire dialoguer un père et son fils à l’aide de signaux. Pour cela on va écrire une commande signaux-pere-fils k s1 s2 ... sn où le fils va émettre vers son père k fois la séquence de signaux donnée en paramètre. On utilisera le signal KILL pour terminer le dialogue.

Afin de ne pas perdre de signaux on va mettre en œuvre le protocole suivant : le père devra envoyer au fils le signal USR1 pour acquitter chaque réception, de son coté le fils devra attendre l’acquittement du père pour poursuivre l’émission.

*/


int main(int argc, char *argv[])
{
	printf("Hello world \n");
	printf("My PID : %d\n", getpid());

	if (argc < 3) {
		fprintf(stderr, "Usage : emettre-signaux pid-cible k s1 s2 ... sn\n");
		exit(EXIT_FAILURE);
	}
	int fpid = fork();

	
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
