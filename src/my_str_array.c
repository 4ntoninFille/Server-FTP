/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** str to word array
*/

#include "serveur.h"

void clean_over_tab(char **array, size_t i, char *str)
{
    while (i < strlen(str)) {
        free(array[i]);
        i++;
    }
}

char **my_str_array(char *str)
{
    int index_tab = 0, index_str = 0;
    if (str[0] == 13) return NULL;
    char **array = malloc(sizeof(char *) * strlen(str) + 1);
    for (size_t i = 0; i < strlen(str); i++) {
        array[i] = malloc(sizeof(char) * strlen(str) + 1);
        memset(array[i], 0, strlen(str));
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\r') {
            array[index_tab][index_str] = '\0';
            index_tab += 1; index_str = 0;
            continue;
        }
        if (str[i] == ' ') continue;
        array[index_tab][index_str] = str[i]; index_str += 1;
    }
    clean_over_tab(array, index_tab + 1, str);
    array[index_tab][index_str] = '\0';
    array[index_tab + 1] = NULL;
    return (array);
}

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}