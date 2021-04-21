/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** LIST command
*/

#include "serveur.h"

void send_to_client(client_node_t *client, int fd)
{
    char *line = get_next_line(fd);
    while (line) {
        dprintf(*client->fd_transfer, "%s\r\n", line);
        free(line);
        line = get_next_line(fd);
    }
}

int command_run(char *cmd)
{
    FILE *file = popen(cmd, "r");
    int fd = fileno(file);

    return (fd);
}

char *create_command(serv_env_t *serv, client_node_t *client)
{
    char ls[] = "ls";
    int len = strlen(ls) + 1 +
                    strlen(serv->origin_path) +
                    strlen(client->pwd) + 1 +
                    strlen(client->arg_transfer) + 1;

    char *cmd = malloc(sizeof(char) * (len));

    memset(cmd, 0, len);
    
    cmd = strcat(cmd, ls);
    cmd = strcat(cmd, " ");
    cmd = strcat(cmd, serv->origin_path);
    cmd = strcat(cmd, client->pwd);
    cmd = strcat(cmd, "/");
    cmd = strcat(cmd, client->arg_transfer);

    return (cmd);
}

void list_call(serv_env_t *serv, client_node_t *client)
{
    int fd_cmd = 0;
    char *cmd = create_command(serv, client);

    fd_cmd = command_run(cmd);
    send_to_client(client, fd_cmd);

    dprintf(client->fd,
        "150 File status okay; about to open data connection.\r\n");
}

void list_command(client_node_t *client, char **array)
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
    *client->type_transfer = 1;
    client->data_on = 0;
}