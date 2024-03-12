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

// EXEMPLE DU COURS //

*/


int main(int argc, char *argv[])
{
    int fd = open("test_partage.txt", O_WRONLY);

    if (fork() > 0)
    // père
        write(fd, "Hello", 5);
    else
    // fils
        write(fd, "World", 5);

    close(fd);
	return EXIT_SUCCESS;
}

// HelloWorld
