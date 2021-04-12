/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** user connection function
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

void user_connection(client_node_t *client, char *name)
{
    client->name = str_format(name);
    printf("%s\n", client->name);
}

int user_connection_check(client_node_t *client, char **array)
{
    char msg[256] =  "530 Please login with USER and PASS.\r\n";
    if (strcmp(array[0], "USER\r") == 0 && array[1]) {
        user_connection(client, array[1]);
    } else if (strcmp(array[0], "PASS") == 0) {
        
    }
    if (!client->name) {
        write(client->fd, msg, strlen(msg));
        return (-1);
    }
    if (!client->pass) {
        write(client->fd, msg, strlen(msg));
        return (-1);
    }
    return (0);
}