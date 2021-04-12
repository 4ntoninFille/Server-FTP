/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** main.c
*/

#include "serveur.h"

int error_handling(int ac)
{
    if (ac != 3)
        return 1;
    return 0;
}

void main_loop(serv_env_t *serv)
{
    fd_set current_sockets, ready_sockets;
    FD_ZERO(&current_sockets);
    FD_SET(serv->serveur_fd, &current_sockets);
    serv->current_sockets = &current_sockets;
    while (1) {
        ready_sockets = current_sockets;
        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
            exit(84);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &ready_sockets)) {
                client_selection(serv, i);
            }
        }
    }
}

int main(int ac, char **av)
{
    serv_env_t serv;

    if (error_handling(ac))
        return 84;

    serv = init_server(atoi(av[1]));

    main_loop(&serv);

    close(serv.serveur_fd);
    return (0);
}