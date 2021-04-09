/*
** EPITECH PROJECT, 2021
** boostrap
** File description:
** serveur
*/

#ifndef SERVEUR_H
#define SERVEUR_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <netinet/in.h>

void accept_connection(int serveur, fd_set *curr_sockets);
int initServeur(int port);

#endif