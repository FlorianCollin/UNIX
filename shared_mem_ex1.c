#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>


//#include "utils.h"


/*

## Exercice 1

Écrire un programme qui crée une mémoire partagée permettant de stocker un entier non signé, initialisez la valeur à 1 et ajouter un processus fils. 
Le père et le fils implémenteront une boucle qui lira la valeur de l’entier non signé dans la mémoire partagée, affichera la valeur, 
incrémentera celle-ci et sauvegardera la valeur dans la mémoire partagée. 
Qu’observez-vous ? 
Remédiez-y.

*/

#define NB_ITT 4

int main(int argc, char *argv[]) {
	printf("Hello world \n");
	/*
	void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);

	       MAP_ANONYMOUS
              The mapping is not backed by any file; its contents are initialized to zero.  The fd ar‐
              gument is ignored; however, some implementations require fd to be  -1  if  MAP_ANONYMOUS
              (or  MAP_ANON)  is  specified, and portable applications should ensure this.  The offset
              argument should be zero.  The use of MAP_ANONYMOUS in  conjunction  with  MAP_SHARED  is
              supported on Linux only since kernel 2.4.



	*/
	unsigned int *shared_int = mmap(NULL, sizeof(unsigned int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (shared_int == MAP_FAILED) {
		perror("mmap fail !");
		exit(EXIT_FAILURE);
	}

	*shared_int = 1;

	int fpid = fork();
	if (fpid == -1){
		perror("fork fail !");
		exit(EXIT_FAILURE);
	}

	if (fpid == 0) {
		// fils
		// unsigned int tmp = 0;
		for (int i = 0; i<NB_ITT; i++) {
			printf("fils : %d\n", *shared_int);
			(*shared_int)++;
			sleep(1);
		}

	} else {
		for (int i = 0; i<NB_ITT; i++) {
			printf("père : %d\n", *shared_int);
			(*shared_int)++;
			//sleep(1);
		}
		wait(NULL);
	}

	if (munmap(shared_int, sizeof(unsigned int)) == -1) {
        perror("munmap fail !");
        exit(EXIT_FAILURE);
    }


	return EXIT_SUCCESS;
}
