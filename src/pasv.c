/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** PASV command
*/

#include "serveur.h"

char *ip_format(const char *ip)
{
    char *new_str = malloc(sizeof(char) * (strlen(ip) + 1));
    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] == '.') {
            new_str[i] = ',';
        } else {
            new_str[i] = ip[i];
        }
    }
    new_str[strlen(ip)] = '\0';
    return (new_str);
}

int init_adresse(struct sockaddr_in *myaddr, int fd)
{
    int port = 1024;
    myaddr->sin_family = AF_INET, myaddr->sin_port = htons(port);
    myaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    while (bind(fd, (struct  sockaddr *) myaddr, sizeof(*myaddr)) == -1 &&
            port <= 5000) {
        port += 1; myaddr->sin_port = htons(port);
    }
    if (port > 5000) return (0);
    return (port);
}

int init_data_transfer(serv_env_t *serv, client_node_t *client, const char *ip)
{
    int fd = 0, port = 0;
    char *format_ip = NULL;
    struct sockaddr_in myaddr;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("erreur socket creation\n"); exit(84);
    }
    memset(&myaddr, 0, sizeof(myaddr));
    if ((port = init_adresse(&myaddr, fd)) == 0) return (0);
    listen(fd, 1);

    format_ip = ip_format(ip);
    dprintf(client->fd, "227 Entering Passive Mode (%s,%d,%d)\r\n",
            format_ip, port / 256, port % 256);
    data_transfer(serv, client, fd);
    free(format_ip);
    return (fd);
}

void pasv_command(serv_env_t *serv, client_node_t *client)
{
    struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&serv->serv_adrr;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &ipAddr, ip_str, INET_ADDRSTRLEN );

    init_data_transfer(serv, client, ip_str);

    client->data_on = 1;
}