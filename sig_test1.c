#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Fonction de gestion du signal SIGINT
void handle_sigint(int sig) {
    printf("Hello\n");
    //signal(SIGINT, handle_sigint);
}

int main() {
    // Définir le gestionnaire de signal pour SIGINT
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Erreur lors de la configuration du gestionnaire de signal");
        exit(EXIT_FAILURE);
    }

    // Boucle infinie
    while (1) {
        // Permet de maintenir le processus actif
    }

    return 0;
}
