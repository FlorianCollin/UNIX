#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"

// EXERCICE 2,3,4

int main(int argc, char *argv[])
{
    int status;


    pid_t fpid = fork();

    if (fpid == -1) {
        fprintf(stderr, "fork fail!");
        return EXIT_FAILURE;
    }


    if (fpid == 0){
        // Fils
        printf("Je m'appelle %d et je suis le fils de %d\n", getpid(), getppid());
    } else {
        // Père
        wait (&status);
        /* man page :
        WIFEXITED(wstatus)
              returns true if the child terminated normally, that is, by calling exit(3) or  _exit(2),
              or by returning from main().
        */
        if (WIFEXITED (status))
        printf ("fils OK : status = %d\n", WEXITSTATUS (status));
        else{
            printf ("Fils fail\n");
            return EXIT_FAILURE;
        }
        printf("Je m'appelle %d et mon fils est %d\n", getpid(), fpid);
    }

    /*

    // TERMINAL OUTPUT //

    Je m'appelle 78394 et je suis le fils de 78393
    fils OK : status = 0
    Je m'appelle 78393 et mon fils est 78394

    
    */



    return EXIT_SUCCESS;
}
