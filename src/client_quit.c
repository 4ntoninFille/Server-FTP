/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** client QUIT
*/

#include "serveur.h"

void quit_command(client_node_t *client, char **array, char *command)
{
    char msg[256] = "221 Service closing control connection.\r\n";

    write(client->fd, msg, strlen(msg));
    close(client->fd);

    free(command);
    free_array(array);
}