/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** read select fd
*/

#include "serveur.h"

int compar(const char *s1, const char *s2)
{
    if (strlen(s1) != strlen(s2)) {
        printf("aie\n");
        return (-1);
    }
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            printf("%d, %d aeie\n", s1[i], s2[i]);
            return (-1);
        }
    }
    return (1);
}

int client_command(int fd_client, const char *command)
{
    if (strcmp(command, "QUIT\r") == 0) {
        write(fd_client, "221 Service closing control connection.\r\n", 
            sizeof("221 Service closing control connection.\r\n"));
        close(fd_client);
        return (-1);
    } else {
        write(fd_client, "500 Unknown command.\r\n",
            sizeof("500 Unknown command.\r\n"));
    }
    return (0);
}

void client_selection(serv_env_t *serv, int fd_client)
{
    if (fd_client == serv->serveur_fd) {
        accept_connection(serv->serveur_fd, serv->current_sockets);
    } else {
        if (client_command(fd_client, get_next_line(fd_client)) < 0) {
            FD_CLR(fd_client, serv->current_sockets);
        } else {
            FD_SET(fd_client, serv->current_sockets);
        }
    }
}