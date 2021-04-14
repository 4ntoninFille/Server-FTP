/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** NOOP command
*/

#include "serveur.h"

void noop_command(int fd)
{
    char msg[256] = "200 Command okay.\r\n";
    write(fd, msg, strlen(msg));
}