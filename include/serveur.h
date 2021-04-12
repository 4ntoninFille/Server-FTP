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

typedef struct client_node_s
{
    int     fd;
    int     pass;

    char    *pwd;
    char     *name;

    struct client_node_s *next;
} client_node_t;


typedef struct serv_env_s 
{
    int              serveur_fd;
    char            *origin_path;

    client_node_t   *list_client;
    fd_set          *current_sockets;
} serv_env_t;

void            push_back_client(serv_env_t *serv, int fd);
void            pop_client(serv_env_t *serv, int fd);
void            print_list(serv_env_t *serv);
client_node_t*  find_client(serv_env_t *serv, int fd);

void accept_connection(serv_env_t *serv, fd_set *curr_sockets);
void client_selection(serv_env_t *serveur, int fd_client);
serv_env_t init_server(int port, char *origine_path);

char**  my_str_array(char *str);
void    free_array(char **array);

int     user_connection_check(client_node_t *client, char **array);

#endif