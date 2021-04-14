/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** client list function
*/

#include "serveur.h"

void help_command(int fd)
{
    dprintf(fd, "214 Help message.\r\n");
}