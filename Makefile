# ----- SERVEUR

NAME_SERVEUR = serveur

HEADER_SERVEUR = dir_serveur/includes/serveur.h

SRC_SERVEUR = \
dir_serveur/src/serveur_main.c \
dir_serveur/src/tools.c \
dir_serveur/src/serveur_init.c \
dir_serveur/src/serveur_main_loop.c

OBJ_SERVEUR = $(SRC_SERVEUR:.c=.o)

# ----- CLIENT

NAME_CLIENT = client

HEADER_CLIENT = dir_client/includes/client.h

SRC_CLIENT = dir_client/src/client_main.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# ----- Compilation command

CC = gcc -g -Wall -Werror -Wextra

# ----- Rules

all : $(NAME_SERVEUR) $(NAME_CLIENT)

$(NAME_SERVEUR) : $(OBJ_SERVEUR)
	$(CC) -o $(NAME_SERVEUR) $(OBJ_SERVEUR)

$(NAME_CLIENT) : $(OBJ_CLIENT)
	$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT)

clean :
	rm -rf $(OBJ_SERVEUR) $(OBJ_CLIENT)

fclean : clean
	rm -rf $(NAME_SERVEUR) rm -rf $(NAME_CLIENT)

re : fclean all

.PHONY : all clean fclean re