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
#include <dirent.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

typedef enum {
    NONE,
    PASSIVE,
    ACTIVE
} data_mode_t;

typedef struct client_node_s
{
    int     fd;
    int     pass;
    int     fd_transfer;

    char    *pwd;
    char     *name;

    struct client_node_s *next;
} client_node_t;

typedef struct serv_env_s 
{
    int                 serveur_fd;
    data_mode_t         data_mode;
    char                *origin_path;

    struct sockaddr_in  serv_adrr;
    client_node_t       *list_client;
    fd_set              *current_sockets;
} serv_env_t;

void            push_back_client(serv_env_t *serv, int fd);
void            pop_client(serv_env_t *serv, int fd);
void            print_list(serv_env_t *serv);
client_node_t*  find_client(serv_env_t *serv, int fd);

void        accept_connection(serv_env_t *serv, fd_set *curr_sockets);
void        client_selection(serv_env_t *serveur, int fd_client);
serv_env_t  init_server(int port, char *origine_path);

char*   str_format(char *str);
char**  my_str_array(char *str);
void    free_array(char **array);

int     user_connection_check(client_node_t *client, char **array);

void    quit_command(client_node_t *client, char **array, char *command);
void    noop_command(int fd);
void    help_command(int fd);
void    pwd_command(client_node_t *client);
void    pasv_command(serv_env_t *serv, client_node_t *client);
void    stor_command(serv_env_t *serv, client_node_t *client);
void    cwd_command(serv_env_t *serv, client_node_t *client, char **array);

#endif