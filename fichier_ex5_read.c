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

int read_data(char *fichier, int position);

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Arguments error ! : Usage : lire-entier fichier position\n");
		exit(EXIT_FAILURE);
	} else {
		// affiche des arguments pour debug
		printf("Agument :\nfichier : %s \nposition : %s\n", argv[1], argv[2]);
	}

	int position = atoi(argv[2]); // possible error !

	read_data(argv[1], position);


	return EXIT_SUCCESS;
}



int read_data(char *fichier, int position) {
	
	// Ouverture
	int fd = open(fichier, O_RDONLY|O_CREAT, 0644); // fichier existant
	if (fd == -1) {
		fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Déplacement
	// lseek(2) : off_t lseek(int fd, off_t offset, int whence);
	int current_position = lseek(fd, position, SEEK_SET);
	if (current_position == -1) {
		fprintf(stderr, "Erreur lors du déplacement dans le fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		printf("Position acutuel dans le fichier : %d\n", current_position);
	}

	u_int32_t valeur;

	// Écriture
	int nb_octets = read(fd, &valeur, 4);
	if (nb_octets == -1) {
		fprintf(stderr, "Erreur lors de la lecture dans le fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		printf("Nombre d'octets lu dans le fichier : %d (%d bits)\n", nb_octets, nb_octets*8);
	}

	printf("Valeur lu : %d\n", valeur);

	if (close(fd) == -1) {
		fprintf(stderr,"Erreur lors de la fermeture du fichier : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;

}
