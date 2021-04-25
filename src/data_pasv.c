/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** PASV command
*/

#include "serveur.h"

void *create_shared_memory(size_t size)
{
    int protection = PROT_READ | PROT_WRITE;

    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, protection, visibility, -1, 0);
}

void call_command(serv_env_t *serv, client_node_t *client)
{
    if (*client->type_transfer == 1) {
        list_call(serv, client);
    }

    if (*client->type_transfer == 2) {
        retr_call(serv, client);
    }
}

void data_transfer(serv_env_t *serv, client_node_t *client, int fd_listner)
{
    int stock = -1;
    client->fd_transfer = create_shared_memory(sizeof(int));
    client->type_transfer = create_shared_memory(sizeof(int));
    client->arg_transfer = create_shared_memory(sizeof(int));
    *client->fd_transfer = -1;
    *client->type_transfer = 0;
    if (fork() == 0) {
        *client->fd_transfer = accept(fd_listner, NULL, NULL);
        stock = *client->fd_transfer;
        while (*client->type_transfer == 0) {}
        call_command(serv, client);
        dprintf(client->fd, "226 Closing data connection.\r\n");
        close(stock);
        client->type_transfer = NULL;
        client->fd_transfer = NULL;
        free(client->arg_transfer);
        close(fd_listner);
        exit(0);
    }
}