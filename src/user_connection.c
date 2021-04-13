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
    char msg[256] = "230 User logged in, proceed.\r\n";
    char msg2[256] = "331 User name okay, need password.\r\n";

    client->name = str_format(name);
    write(client->fd, msg2, strlen(msg2));

    (void)msg;
}

void  user_pass(client_node_t *client)
{
    char msg[256] = "230 User logged in, proceed.\r\n";
    char msg2[256] = "332 Need account for login.\r\n";
    if (!client->name) {
        write(client->fd, msg2, strlen(msg2));
        return;
    }
    client->pass = 1;
    write(client->fd, msg, strlen(msg));
}

int user_connection_check(client_node_t *client, char **array)
{
    if (strcmp(array[0], "USER") == 0 && array[1]) { 
        user_connection(client, array[1]);
        return (0);
    } else if (strcmp(array[0], "PASS") == 0) {
        user_pass(client);
    }
    return (0);
}