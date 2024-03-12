#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

/*

// EXERCICE 9 //

Reprenez l’exercice précédent, 
mais ce recouvrement devra être effectué par un processus fils créé dans le second programme.

*/


int main(int argc, char *argv[])
{
	// prog 1
	printf("Hello world \n");
	return EXIT_SUCCESS;
}
