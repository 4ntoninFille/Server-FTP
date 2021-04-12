/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** header
*/


#ifndef READ_SIZE
#define READ_SIZE 1
#endif

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void my_putchar(char c);
void my_putstr(char *str);
char *get_next_line(int fd);

#endif
