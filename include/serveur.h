/*
** EPITECH PROJECT, 2021
** boostrap
** File description:
** serveur
*/

#ifndef SERVEUR_H
#define SERVEUR_H

#include "get_next_line.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <netinet/in.h>

typedef struct serv_env_s 
{
    int serveur_fd;
    fd_set *current_sockets;

} serv_env_t;

void accept_connection(int serveur, fd_set *curr_sockets);
void client_selection(serv_env_t *serveur, int fd_client);
serv_env_t init_server(int port);

#endif