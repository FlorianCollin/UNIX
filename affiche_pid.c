#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
	printf("Voci mon pid : %d\n", getpid()); 
	return EXIT_SUCCESS;
}
