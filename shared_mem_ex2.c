#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>



#include "utils.h"

/*
## Exercice 2

Écrire un programme qui permet de trouver la plus petite valeur d’un tableau en parallélisant la recherche avec N processus, N étant un argument donné en entrée du programme.
Le tableau sera de taille N^5 et sera généré aléatoirement au début du programme dans une mémoire partagée.
Le seul moyen de communication autorisé entre les processus sera la mémoire partagée.

*/

int main(int argc, char *argv[]) {
	printf("Hello world \n");
	if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

	int N = atoi(argv[1]);
    int size = N*N*N*N*N; // N^5

    int segmentSize = size / N;

	int *data = mmap(NULL, ((size_t)size + 1) * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *minValue = data + size; // pointeur vers la plus petite valeur enregistrer à la fin
    *minValue = 100;
    srand(time(NULL));
	// Création du tableau
	for (int i = 0; i < size; i++) {
			*(data+i) = rand() % 100;
	}


	for (int i = 0; i < N; i++) {
        pid_t fpid = fork();
		if (fpid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
		}

        if (fpid == 0) { 
			// fils
            int localMin = 100;
            for (int j = i * segmentSize; j < (i + 1) * segmentSize; j++) {
                if (*(data + j) < localMin) {
                    localMin = *(data + j);
                }
            }
            if (localMin < *minValue) {
                *minValue = localMin;
            }
            exit(EXIT_SUCCESS); // Fin du processus enfant
        }
    }
	// on attend la fin de TOUT les procesus, on attend ainsi que wait retourne -1 car il n'y a plus de procesus à attendre 
	while (wait(NULL) > 0);

	for (int i = 0; i < size; i++) {
		printf("tab[%d]=%d\n", i, *(data+i));
	}
	printf("minValue ! %d\n", *minValue);

	munmap(data, (size + 1) * sizeof(int));

	return EXIT_SUCCESS;
}
