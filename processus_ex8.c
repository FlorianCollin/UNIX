#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

/*

// EXERCICE 8 //

Créez un premier programme très simple (qui fait juste un printf par exemple) 
puis créez un second programme qui va effectuer un recouvrement en appelant ce premier programme.

*/

int main(int argc, char *argv[])
{
	printf("Hello world\n");
	return EXIT_SUCCESS;
}
