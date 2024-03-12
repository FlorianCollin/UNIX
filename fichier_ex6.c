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


int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("")
	}
	return EXIT_SUCCESS;
}
