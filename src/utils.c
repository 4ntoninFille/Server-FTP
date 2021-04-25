/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** utils function
*/

#include "serveur.h"

char *create_origin_path(serv_env_t *serv, char *path)
{
    int len = strlen(serv->origin_path) +
                strlen(path) + 1;

    char *cmd = malloc(sizeof(char) * (len));

    memset(cmd, 0, len);

    cmd = strcat(cmd, serv->origin_path);
    cmd = strcat(cmd, path);

    return (cmd);
}

char *create_origin_path_retr(serv_env_t *serv, client_node_t *client)
{
    int len = strlen(serv->origin_path) +
                strlen(client->pwd) + 1 +
                strlen(client->arg_transfer) + 1;

    char *cmd = malloc(sizeof(char) * (len));

    memset(cmd, 0, len);

    cmd = strcat(cmd, serv->origin_path);
    cmd = strcat(cmd, client->pwd);
    cmd = strcat(cmd, "/");
    cmd = strcat(cmd, client->arg_transfer);

    return (cmd);
}