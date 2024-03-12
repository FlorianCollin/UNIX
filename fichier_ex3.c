#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

#define BUFF_SIZE 2

/*

// EXERCICE 3 //

Écrire une commande mycat qui écrive caractère par caractère le contenu de son entrée standard sur sa sortie standard.
Pour effectuer les entrées-sorties on utilisera le couple de fonctions read / write. 
Testez votre programme en lui faisant afficher le code source, comme ceci :

$ ./mycat < mycat.c
Modifiez votre programme pour lire/écrire N caractères à la fois (en définissant une constante dans le source).

*/


int mycat();


int main(int argc, char *argv[])
{
	mycat();

	return EXIT_SUCCESS;
}

int mycat() {
	char buff[BUFF_SIZE]; // on utilisera un buffer de 1 octet
	// lecture sur stdin
	printf("Start : mycat\n");


	while(read(STDIN_FILENO, &buff, BUFF_SIZE) > 0) {
		for (int k = 0; k < BUFF_SIZE; k++) {
			printf("%c", buff[k]);
		}
		
	}

	printf("\n");
	printf("End : mycat\n");

	return 0;
}
/*

florian@florian-Latitude-5310:~/MI203$ ./fichier_ex3 < file.txt
Start : mycat
Hello World
End : mycat

*/