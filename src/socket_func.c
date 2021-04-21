/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** creation of socket
*/

#include "serveur.h"

void accept_connection(serv_env_t *serv, fd_set *current_sockets)
{
    int client = accept(serv->serveur_fd, NULL, NULL);

    push_back_client(serv, client);

    FD_SET(client, current_sockets);
    dprintf(client, "220 Service ready for new user.\r\n");
}

void serv_init(serv_env_t *serv, char *origine_path)
{
    serv->list_client = NULL;
    serv->origin_path = origine_path;
    serv->serveur_fd = 0;
}

serv_env_t init_server(int port, char *origine_path)
{
    int fd = 0;
    serv_env_t serv;
    struct sockaddr_in myaddr;
    serv_init(&serv, origine_path);
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("erreur socket\n"); exit(84);
    }
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct  sockaddr *) &myaddr, sizeof(myaddr)) == -1) {
        printf("erreur bind\n"); close(fd); exit(84);
    }
    serv.serveur_fd = fd;
    serv.serv_adrr = myaddr;
    listen(fd, 100);
    return (serv);
}