/*
** EPITECH PROJECT, 2019
** get_next_line.c
** File description:
** read a line
*/

#include "get_next_line.h"

int my_strlen(char const *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        count++;
    }
    return (count);
}

char *my_strncpy(char *buff, char *copy, int n)
{
    int index = 0;
    while (index < n && copy[index] != '\0') {
        buff[index] = copy[index];
        index++;
    }
    buff[index] = '\0';
    return (buff);
}

char *add(char *line, char *buff, int step, int *begin)
{
    char *newline;
    int len2;
    if (line != 0)
        len2 = my_strlen(line);
    else
        len2 = 0;
    newline = malloc(sizeof(char) * (len2 + step + 1));
    if (newline == 0) {return (0);}
    if (line != 0)
        my_strncpy(newline, line, len2);
    else
        my_strncpy(newline, "", len2);
    newline[len2 + step] = '\0';
    my_strncpy(newline + len2, buff + *begin, step);
    if (line)
        free(line);
    *begin = *begin + step + 1;
    return (newline);
}

char *get_next_line(int fd)
{
    static char buff[READ_SIZE];
    static int begin;
    static int len = 0;
    char *line = 0;
    int step = 0;
    while (1) {
        if (len <= begin) {
            begin = 0;
            step = 0;
            len = read(fd, buff, READ_SIZE);
        }
        if (len == 0) {return (line);}
        if (len == -1) {return (0);}
        if (buff[begin + step] == '\n') {
            line = add(line, buff, step, &begin);
            return (line);
        }
        if (begin + step == len - 1) {line = add(line, buff, step + 1, &begin);}
        step += 1;
    }
}
