/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** main.c
*/

#include "serveur.h"

int errorHandling(int ac)
{
    if (ac != 3)
        return 1;
    return 0;
}

void main_loop(int serveur)
{
    fd_set current_sockets, ready_sockets;
    FD_ZERO(&current_sockets);
    FD_SET(serveur, &current_sockets);

    while (1) {
        ready_sockets = current_sockets;
        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
            exit(EXIT_FAILURE);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &ready_sockets)) {
                if (i == serveur) {
                    accept_connection(serveur, &current_sockets);
                } else {
                    FD_CLR(i, &current_sockets);
                }
            }
        }
    }
}

int main(int ac, char **av)
{
    int serveur = 0;

    if (errorHandling(ac))
        return 84;

    if ((serveur = initServeur(atoi(av[1]))) == -1)
        return 84;

    main_loop(serveur);

    close(serveur);
    return (0);
}