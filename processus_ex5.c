#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    pid_t fpid = fork();

    if (fpid == -1){
        perror("Erreur fork!");
        exit(EXIT_FAILURE);
    }

    if (fpid == 0) {
        // fils
        // on attend quelque seconde
        sleep(5);
        // affichage du pid du père
        printf("PID du père :%d\n", getppid());
        exit(EXIT_SUCCESS);
    }

    
    return 0;
}
