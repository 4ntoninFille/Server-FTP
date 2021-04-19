/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** PASV command
*/

#include "serveur.h"

void* create_shared_memory(size_t size)
{
    int protection = PROT_READ | PROT_WRITE;

    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, protection, visibility, -1, 0);
}

void data_transfer(client_node_t *client, int fd_listner)
{
    int stock = -1;
    client->fd_transfer = create_shared_memory(sizeof(int));
    *client->fd_transfer =  -2;
    if (fork() == 0) {
        *client->fd_transfer = accept(fd_listner, NULL, NULL);
        stock = *client->fd_transfer;
        while (*client->fd_transfer != -1) {
        }
        dprintf(client->fd, "226 Closing data connection.\r\n");
        close(stock);
        client->fd_transfer = NULL;
        close(fd_listner);
        exit(0);
    }
}