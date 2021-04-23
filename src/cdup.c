/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** CDUP command
*/

#include "serveur.h"

void cdup_command(client_node_t *client)
{
    int lock = 1;
    char *new = NULL;
    if (strlen(client->pwd) == 1) {
        dprintf(client->fd, "504 Command not implemented for that parameter.\r\n");
        return;
    }
    new = malloc(sizeof(char) * strlen(client->pwd));
    memset(new, 0, strlen(client->pwd));
    for (int i = strlen(client->pwd) - 1; i >= 0; i--) {
        if (client->pwd[i] == '/' && lock) {
            lock = 0; new[i] = '\0'; continue;
        }
        if (lock) continue;
        new[i] = client->pwd[i];
    }
    if (new[0] == '\0') {
        new[0] = '/';
        new[1] = '\0';
    }
    free(client->pwd);
    client->pwd = new;
    dprintf(client->fd, "200 Command okay.\r\n");
}