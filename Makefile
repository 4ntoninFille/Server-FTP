##
## EPITECH PROJECT, 2021
## Mini-Pacman
## File description:
## Makefile
##

SRC			=	src/main.c		\
				src/socket_func.c	\
				src/select_client.c 	\
				src/client_list.c	\
				src/client_quit.c	\
				src/get_next_line.c 	\
				src/user_connection.c 	\
				src/my_str_array.c 	\
				src/pasv.c		\
				src/stor.c		\

CFLAGS 	+=	-Wall -Wextra -I./include -g3
NAME 		= 	myftp

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
