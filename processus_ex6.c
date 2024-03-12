#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>


#include "utils.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Argument missing !\n");
		return(EXIT_FAILURE);
	}
	for(int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	int N = atoi(argv[1]);


	printf("N = %d\n", N);

	for (int i = 0; i < N; i++) {
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork fail !\n");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) {
			// fils
			printf("mon numéro de rang est : %d et je mon pid est : %d\n", i, getpid());
			exit(EXIT_SUCCESS);
		}
	}


	// puis on doit attendre la terminaison des N processus fils
	
	for (int i = 0; i < N; i++) {
		int status;
		wait(&status);
		int pid_tmp = WIFEXITED(status);
		if (pid_tmp) {
			printf("processus fils %d termné\n", pid_tmp);
		} else {
			printf("Erreur dans le processus fils !!");
		}
	}

	printf(" END ! \n");

	
	return EXIT_SUCCESS;
}
