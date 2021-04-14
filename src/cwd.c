/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** CWD command
*/

#include "serveur.h"

char *format_path(char *path)
{
    char *new = malloc(sizeof(char) * (strlen(path) + 1));
    int index = 0;
    int i = 0;
    if (path[0] == '/') {
        index += 1;
    }

    while (path[index] != '\0') {
        new[i] = path[index];
        index += 1;
        i += 1;
    }
    new[i] = '\0';

    if (new[i - 1] == '/') {
        new[i - 1] = '\0';
    }
    return (new);
}

void cwd_command(serv_env_t *serv, client_node_t *client, char **array)
{
    static int first = 1;
    char *new_path = NULL;
    if (!array[1]) return;
    char *form_path = format_path(array[1]);
    new_path = malloc(sizeof(char) * (strlen(form_path) + 
                                        strlen(serv->origin_path) +
                                        2));
    memset(new_path, 0, strlen(form_path) + strlen(serv->origin_path) + first);
    new_path = strcat(new_path, client->pwd);
    if (first == 2) {
        new_path = strcat(new_path, "/");
    } else {
        first = 2;
    }
    new_path = strcat(new_path, form_path);
    free(client->pwd);
    free(form_path);
    dprintf(client->fd, "250 Requested file action okay, completed.\r\n");
    client->pwd = new_path;
}