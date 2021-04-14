/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** PWD command
*/

#include "serveur.h"

void pwd_command(client_node_t *client)
{
    dprintf(client->fd, "257 \"%s\" created.\r\n", client->pwd);
}