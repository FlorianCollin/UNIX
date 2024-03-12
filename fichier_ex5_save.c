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

// EXERCICE 5 //

Écrire deux commandes pour lire et enregistrer un entier de 32 bits non signé à une position donnée d’un fichier donné.
Les deux commandes auront les prototypes suivants:

enregister-entier fichier position valeur
lire-entier fichier position
Tester ces commandes en utilisant un fichier membre d’un répertoire de votre compte.

Utiliser la commande hexdump pour visualiser le contenu du fichier.

Que constate-t-on si l’on cherche lire / écrire après la fin du fichier?

*/


#define WRITE_AFTER_EOF 0

int save_data(char *fichier, int position, u_int32_t valeur);

int main(int argc, char *argv[])
{
	if (argc != 4) {
		fprintf(stderr, "Arguments error ! : Usage : enregister-entier fichier position valeur\n");
		exit(EXIT_FAILURE);
	} else {
		// affiche des arguments pour debug
		printf("Agument :\nfichier : %s \nposition : %s \nvaleur : %s\n", argv[1], argv[2], argv[3]);
	}

	int position = atoi(argv[2]); // possible error !
	u_int32_t valeur = (u_int32_t)atoi(argv[3]); // possible error !

	save_data(argv[1], position, valeur);

	return EXIT_SUCCESS;
}



int save_data(char *fichier, int position, u_int32_t valeur) {
	
	// Ouverture
	int fd = open(fichier, O_WRONLY|O_CREAT, 0644); // fichier existant
	if (fd == -1) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Déplacement
	// lseek(2) : off_t lseek(int fd, off_t offset, int whence);
	
	// test d'écriture après la fin du fichier :
	int current_position;
	if (WRITE_AFTER_EOF == 0) {
		// déplacement à SET + position
		current_position = lseek(fd, position, SEEK_SET);
	} else {
		// déplacement à END + position
		printf("Attention : déplacement après la fin du fichier \n");
		current_position = lseek(fd, position, SEEK_END);
	}

	// effectue la même chose !

	if (current_position == -1) {
		fprintf(stderr, "Erreur lors du déplacement dans le fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		printf("Position acutuel dans le fichier : %d\n", current_position);
	}

	// Écriture
	int nb_octets = write(fd, &valeur, 4);
	if (nb_octets == -1) {
		fprintf(stderr, "Erreur lors de l'écriture sur le fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		printf("Nombre d'octets ecrit sur le fichier : %d (%d bits)\n", nb_octets, nb_octets*8);
	}

	if (close(fd) == -1) {
		fprintf(stderr,"Erreur lors de la fermeture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;

}

/*
florian@florian-Latitude-5310:~/MI203$ ./fichier_ex5_save fichier_test 10 69
Agument :
fichier : fichier_test 
position : 10 
valeur : 69
Position acutuel dans le fichier : 10
Nombre d'octets ecrit sur le fichier : 4 (32 bits)
florian@florian-Latitude-5310:~/MI203$ ./fichier_ex5_read fichier_test 10
Agument :
fichier : fichier_test 
position : 10
Position acutuel dans le fichier : 10
Nombre d'octets lu dans le fichier : 4 (32 bits)
Valeur lu : 69


Que constate-t-on si l’on cherche lire / écrire après la fin du fichier?
Agument :
fichier : fichier_test 
position : 10 
valeur : 69
Attention : déplacement après la fin du fichier 
Position acutuel dans le fichier : 10
Nombre d'octets ecrit sur le fichier : 4 (32 bits)

Il repart du debut si on fait END + position mais si on fait SET + position alors la taille du fihcier augmente dynamiquemet


lseek()  allows  the  file offset to be set beyond the end of the file (but this does not change the size of the file).  If data is later written at this point, subsequent reads of the data in
       the gap (a "hole") return null bytes ('\0') until data is actually written into the gap.
*/