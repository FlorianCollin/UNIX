#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>

#define NB_ITT 4

int main(int argc, char *argv[]) {
    printf("Hello world \n");

    struct shmbuff {
        unsigned int value;
        sem_t semaphore;
    };

    struct shmbuff *shared = mmap(NULL, sizeof(struct shmbuff), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared == MAP_FAILED) {
        perror("mmap fail !");
        exit(EXIT_FAILURE);
    }

    shared->value = 1;

    if (sem_init(&shared->semaphore, 1, 1) == -1) {
        perror("sem_init fail !");
        exit(EXIT_FAILURE);
    }

    int fpid = fork();
    if (fpid == -1){
        perror("fork fail !");
        exit(EXIT_FAILURE);
    }

    if (fpid == 0) {
        // Processus fils
        for (int i = 0; i < NB_ITT; i++) {
            sem_wait(&shared->semaphore); // lock
            printf("fils : %d\n", shared->value);
            shared->value++;
            printf("fils : incrementation :%d\n", shared->value);
            sem_post(&shared->semaphore); // unlock
            sleep(1);
        }
    } else {
        // Processus père
        for (int i = 0; i < NB_ITT; i++) {
            sem_wait(&shared->semaphore);
            printf("père : %d\n", shared->value);
            shared->value++;
            printf("père : incrementation :%d\n", shared->value);
            sem_post(&shared->semaphore);
			sleep(1);
        }
        wait(NULL);
        
        // Détruit le sémaphore
        sem_destroy(&shared->semaphore);
    }

    if (munmap(shared, sizeof(struct shmbuff)) == -1) {
        perror("munmap fail !");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}


/*

père : 1
père : incrementation :2
fils : 2
fils : incrementation :3
père : 3
père : incrementation :4
fils : 4
fils : incrementation :5
fils : 5
fils : incrementation :6
père : 6
père : incrementation :7
fils : 7
fils : incrementation :8
père : 8
père : incrementation :9


*/