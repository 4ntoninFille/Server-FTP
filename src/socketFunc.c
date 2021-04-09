/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** creation of socket 
*/

#include "serveur.h"

void accept_connection(int serveur, fd_set *current_sockets)
{
    char msg[256] = "220\n";
    int client = accept(serveur, NULL, NULL);

    FD_SET(client, current_sockets);
    write(client, msg, sizeof(msg));
}

int initServeur(int port)
{
    int fd = 0;
    struct sockaddr_in myaddr;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("erreur socket\n");
        return -1;
    }
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct  sockaddr *) &myaddr, sizeof(myaddr)) == -1) {
        printf("erreur bind\n");
        close(fd);
        return -1;
    }

    listen(fd, 10);
    return (fd);
}