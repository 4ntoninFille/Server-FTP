/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** read select fd
*/

#include "serveur.h"

char *str_format(char *str)
{
    char *new = strdup(str);
    for (int i = 0; new[i] != '\0'; i++) {
        if (new[i] == '\r') {
            new[i] = '\0';
        }
    }
    return (new);
}

void noop_command(int fd)
{
    char msg[256] = "200 Command okay.\r\n";
    write(fd, msg, strlen(msg));
}

int client_command(serv_env_t *serv, client_node_t *client, char *command)
{
    char *format_command = str_format(command);
    char **array = my_str_array(format_command);
    free(command);
    if (array && strcmp(array[0], "QUIT") == 0) {
        quit_command(client, array, format_command);
        return (-1);
    }
    if (array && user_connection_check(client, array) > 0) {
        if (strcmp(array[0], "NOOP") == 0) noop_command(client->fd);
        else if (strcmp(array[0], "PASV") == 0) pasv_command(serv, client);
        else if (strcmp(array[0], "STOR") == 0) stor_command(serv, client);
        else {
            write(client->fd, "500 Unknown command.\r\n",
            sizeof("500 Unknown command.\r\n"));
        }
    }
    free(format_command);
    free_array(array);
    return (0);
}

void client_selection(serv_env_t *serv, int fd_client)
{
    if (fd_client == serv->serveur_fd) {
        accept_connection(serv, serv->current_sockets);
    } else {
        if (client_command(serv, find_client(serv, fd_client),
                            get_next_line(fd_client)) < 0) {
            FD_CLR(fd_client, serv->current_sockets);
            pop_client(serv, fd_client);
        } else {
            FD_SET(fd_client, serv->current_sockets);
        }
    }
}