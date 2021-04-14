/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** user connection function
*/

#include "serveur.h"

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

void not_log(client_node_t *client)
{
    char msg[256] = "530 Not logged in.\r\n";
    write(client->fd, msg, strlen(msg));
}

int user_connection_check(client_node_t *client, char **array)
{
    if (strcmp(array[0], "USER") == 0 && array[1]) { 
        user_connection(client, array[1]);
        return (-1);
    }
    if (!client->name) {
        not_log(client);
        return (-1);
    } 
    if (strcmp(array[0], "PASS") == 0) {
        user_pass(client);
        return (-1);
    }
    if (!client->pass) {
        not_log(client);
        return (-1);
    }
    return (1);
}