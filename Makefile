##
## EPITECH PROJECT, 2021
## Mini-Pacman
## File description:
## Makefile
##

SRC			=	src/main.c			\
				src/socket_func.c	\
				src/select_client.c \
				src/get_next_line.c \

CFLAGS 	+=	-Wall -Wextra -I./include
NAME 		= 	serveur

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
