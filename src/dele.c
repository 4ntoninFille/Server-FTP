/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** DELE command
*/

#include "serveur.h"

char *create_command_dele(serv_env_t *serv, client_node_t *client, char *name)
{
    int len = strlen(serv->origin_path) +
                strlen(client->pwd) + 1 +
                strlen(name) + 1;
    char *cmd = malloc(sizeof(char) * len);

    memset(cmd, 0, len);

    cmd = strcat(cmd, serv->origin_path);
    cmd = strcat(cmd, client->pwd);
    cmd = strcat(cmd, "/");
    cmd = strcat(cmd, name);

    return (cmd);
}

void dele_command(serv_env_t *serv, client_node_t *client, char **array)
{
    char *cmd = NULL;

    if (array[1]) {
        cmd = create_command_dele(serv, client, array[1]);
        
        if (remove(cmd) < 0) {
            dprintf(client->fd, "550 Requested action not taken.\r\n");
        } else {
            dprintf(client->fd, "250 Requested file action okay, completed.\r\n");
        }
    }

}