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


// Ce programme est insatisfaisant, il ne permet pas d'écrire le premier caractère de input file ??
// le programme fichier_ex6_2 fourni une correction !

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
	char buff;
	int current_offset = -1;
	// On ce positione à la fin du fichier
	int current_position = lseek(fd_input_file, current_offset, SEEK_END);
	if (current_position == -1) {
		perror("lseek fail !");
		exit(EXIT_FAILURE);
	}

	printf("input file size : %d\n", current_position);

	int read_status;
	int exit_status = 0;
	while (!exit_status) {
		// lecuture dans input file
		read_status = read(fd_input_file, &buff, 1);
		if (read_status == -1) {
			perror("read fail !");
			exit(EXIT_FAILURE);
		}
		
		current_offset--;	
		current_position = lseek(fd_input_file, current_offset, SEEK_END);

		printf("Position courante : %d\n", current_position);

		if(current_position == -1) {
			perror("lseek fail!");
			exit(EXIT_FAILURE);
		}

		if (current_position == 0) {
			exit_status = 1;
		}
		printf("%c\n", buff);
		if (write(fd_output_file, &buff, 1) == -1) {
			perror("write fail !");
			exit(EXIT_FAILURE);
		}
	}
	printf("Read status : %d (errno : %s) \n", read_status, strerror(errno));
	close(fd_input_file);
	close(fd_output_file);
	return EXIT_SUCCESS;
}
