/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** read select fd
*/

#include "serveur.h"

int client_command(client_node_t *client, char *command)
{
    int quit = 0;
    char **array = my_str_array(command);
    if (array && strcmp(array[0], "QUIT\r") == 0) {
        write(client->fd, "221 Service closing control connection.\r\n",
            sizeof("221 Service closing control connection.\r\n"));
        close(client->fd);
        quit = -1;
    } else if (!quit) {
        if (user_connection_check(client, array) > 0) {
        }
        quit = 1;
    } else if (!quit) {
        write(client->fd, "500 Unknown command.\r\n",
            sizeof("500 Unknown command.\r\n"));
    }
    free(command);
    free_array(array);
    return (quit);
}

void client_selection(serv_env_t *serv, int fd_client)
{
    if (fd_client == serv->serveur_fd) {
        accept_connection(serv, serv->current_sockets);
    } else {
        if (client_command(find_client(serv, fd_client),
                            get_next_line(fd_client)) < 0) {
            FD_CLR(fd_client, serv->current_sockets);
            pop_client(serv, fd_client);
        } else {
            FD_SET(fd_client, serv->current_sockets);
        }
    }
}