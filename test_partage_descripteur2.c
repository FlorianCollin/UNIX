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
    pid_t pid = fork();
    int fd = open("test_partage.txt", O_WRONLY);

    if (pid > 0)
        write(fd, "Hello", 5);
    else
        write(fd, "World", 5);

    close(fd);
}

// World

// Dans le cas 2 on a fork avant d'ouvrir (open)

/*
fork() duplique la table des descrpteur ainsi si on le fais avant alors on aurra pas la même que le père !
mais si on le fais après alors oui !!

*/