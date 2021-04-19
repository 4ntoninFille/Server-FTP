/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** LIST command
*/

#include "serveur.h"

void list_command(client_node_t *client)
{
    if (!client->data_on) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return;
    }
    while (*client->fd_transfer == -2) {
    }
    *client->fd_transfer = -1;
    dprintf(client->fd,
        "150 File status okay; about to open data connection.\r\n");
    client->data_on = 0;
}