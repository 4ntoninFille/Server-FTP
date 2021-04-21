/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** client list function
*/

#include "serveur.h"

void push_back_client(serv_env_t *serv, int fd)
{
    client_node_t *new = malloc(sizeof(client_node_t));
    client_node_t *tmp = serv->list_client;
    new->fd = fd;
    new->fd_transfer = NULL;
    new->type_transfer = NULL;
    new->arg_transfer = NULL;
    new->pwd = strdup("/");
    new->name = NULL;
    new->pass = 0;
    new->next = NULL;
    new->data_on = 0;
    if (!tmp) {
        serv->list_client = new;
        return;
    }
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void pop_client(serv_env_t *serv, int fd)
{
    client_node_t *tmp = serv->list_client;
    client_node_t *prev = NULL;

    if (!tmp) return;

    while (tmp && tmp->fd != fd) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (prev) {
        prev->next = tmp->next;
    } else {
        serv->list_client = tmp->next;
    }
    free(NULL);
    free(tmp->pwd);
    free(tmp->name);
    free(tmp);
}

client_node_t *find_client(serv_env_t *serv, int fd)
{
    client_node_t *tmp = serv->list_client;

    while (tmp && tmp->fd != fd) {
        tmp = tmp->next;
    }

    return (tmp);
}

void print_list(serv_env_t *serv)
{
    client_node_t *tmp = serv->list_client;
    while (tmp) {
        printf("%d ", tmp->fd);
        tmp = tmp->next;
    }
    printf("\n");
}