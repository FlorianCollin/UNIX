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

// EXERCICE 6 //

Écrire la commande reverse input-file-name output-file-name qui écrit le miroir du premier fichier dans le second. On utilisera la fonction lseek() pour déterminer la taille du fichier source.

Comment limiter le nombre de lseek ? Le faire.

*/


// Limitation à 2 lseek // cette version est ainsi la définitif de l'exercice 6 !!

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage : reverse input-file-name output-file-name \n");
		exit(EXIT_FAILURE);
	}

	printf("Input file : %s\n", argv[1]);
	printf("Output file : %s\n", argv[2]);

	int fd_input_file = open(argv[1], O_RDONLY);
	if (fd_input_file == -1) {
		perror("open input file fail !");
		exit(EXIT_FAILURE);
	}
	int fd_output_file = open(argv[2], O_WRONLY);
	if (fd_output_file == -1) {
		perror("open output file fail !");
		exit(EXIT_FAILURE);
	}

	int taille_fichier = lseek(fd_input_file, 0, SEEK_END);
	if (taille_fichier == -1) {
		perror("lseek fail !");
		exit(EXIT_FAILURE);
	}
	// allocation dynamique

	char *buffer_d = (char *)malloc(1*taille_fichier);
	if (buffer_d == NULL) {
		perror("malloc fail !");
		exit(EXIT_FAILURE);
	}

	printf("input file size : %d\n", taille_fichier);

	if(lseek(fd_input_file, 0, SEEK_SET) == -1) {
		perror("lseek fail !");
		exit(EXIT_FAILURE);
	}

	int read_status;
	// int exit_status = 0;
	

	read_status = read(fd_input_file, buffer_d, taille_fichier);
	if (read_status == -1) {
		perror("read fail !");
		exit(EXIT_FAILURE);
	}
	printf("Read status control: %d \terrno : %s \n", read_status, strerror(errno));
	printf("Nombre de caractère lue sur input-file : %d.\n", read_status);
	// for debug
	for (int k = 0; k < read_status; k++) {
		printf("caractère n°%d : %c\n", k, *(buffer_d + k));
	}
	
	for (int k = read_status -1; k >= 0; k--) {
		if (write(fd_output_file, buffer_d+k, 1) == -1) {
			perror("write fail !");
			exit(EXIT_FAILURE);
		}		
	}

	free(buffer_d);
	close(fd_input_file);
	close(fd_output_file);
	return EXIT_SUCCESS;
}
