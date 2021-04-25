/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** RETR command
*/

#include "serveur.h"

int download_file(client_node_t *client, char *path)
{
    char *line = NULL;
    int fd_file = open(path, O_RDONLY);

    if (fd_file < 0) {
        return (-1);
    }

    line = get_next_line(fd_file);
    while (line) {
        dprintf(*client->fd_transfer, "%s\r\n", line);
        line = get_next_line(fd_file);
    }

    close(fd_file);
    return (0);
}

void retr_call(serv_env_t *serv, client_node_t *client)
{
    char *path = create_origin_path_retr(serv, client);

    if (download_file(client, path) < 0) {
        dprintf(client->fd, "550 Failed to open file.\r\n");
    } else {
        dprintf(client->fd,
        "150 File status okay; about to open data connection.\r\n");
    }

    free(path);
}

void retr_command(client_node_t *client, char **array)
{
    if (!client->data_on) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return;
    }
    while (*client->fd_transfer == -1) {
    }
    if (array[1]) {
        memcpy(client->arg_transfer, array[1], strlen(array[1]));
    }
    *client->type_transfer = 2;
    client->data_on = 0;
}