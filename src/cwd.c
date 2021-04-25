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

int cwd_back(client_node_t *client, char *path)
{
    if (strcmp(path, "..") == 0) {
        cdup_command(client);
        return (1);
    }
    return (0);
}

int is_exist_path(serv_env_t *serv, client_node_t *client, char *path_racine)
{
    int err = 0;
    DIR *dir;
    char *path = create_origin_path(serv, path_racine);
    dir = opendir(path);
    if (!dir) {
        err = -1;
        dprintf(client->fd, "550 Failed to change directory.\r\n");
        free(path_racine);
    }
    closedir(dir);
    free(path);
    return (err);
}

void cwd_command(serv_env_t *serv, client_node_t *client, char **array)
{
    int first = 2;
    char *new_path = NULL;
    if (!array[1]) return;
    char *form_path = format_path(array[1]);
    if (cwd_back(client, form_path)) return;
    if (strlen(client->pwd) == 1) first = 1;
    new_path = malloc(sizeof(char) * (strlen(form_path) +
                                        strlen(client->pwd) +
                                        first));
    memset(new_path, 0, strlen(form_path) + strlen(client->pwd) + first);
    new_path = strcat(new_path, client->pwd);
    if (first == 2)
        new_path = strcat(new_path, "/");
    new_path = strcat(new_path, form_path);
    free(client->pwd);
    free(form_path);
    if (is_exist_path(serv, client, new_path) < 0)
        return;
    client->pwd = new_path;
    dprintf(client->fd, "250 Requested file action okay, completed.\r\n");
}