#!/bin/bash

# Lancement du programme
./sig_ex5_2 &

# Récupération du PID du programme
PID=$!

# Attente de 1 seconde pour laisser le temps au programme de démarrer
sleep 1

# Envoi du signal SIGUSR1
echo "Envoi du signal SIGUSR1"
kill -SIGUSR1 $PID
sleep 1

# Envoi du signal SIGUSR2
echo "Envoi du signal SIGUSR2"
kill -SIGUSR2 $PID
sleep 1

# Envoi du signal SIGALRM
echo "Envoi du signal SIGALRM"
kill -SIGALRM $PID
sleep 1

# Envoi du signal SIGINT (Ctrl+C)
echo "Envoi du signal SIGINT (Ctrl+C)"
kill -SIGINT $PID
sleep 1

# Attente de la terminaison du programme
wait $PID

echo "Test terminé."
