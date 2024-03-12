#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    // Ouvre un fichier quelconque
    int fd = open("file.txt", O_RDONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Affiche le descripteur de fichier associé
    printf("Descripteur de fichier du fichier ouvert : %d\n", fd);

    // Crée un processus fils
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors de la création du processus fils");
        return 1;
    } else if (pid == 0) {
        // Code du processus fils
        execl("./test", "./test", (char *)NULL);
        perror("Erreur lors de l'exécution du programme dans le processus fils");
        exit(1);
    } else {
        // Code du processus parent
        wait(NULL);  // Attends que le processus fils se termine
    }

    // Ferme le fichier
    close(fd);

    return 0;
}
