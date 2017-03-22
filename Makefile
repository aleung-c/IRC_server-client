# ----- SERVEUR

NAME_SERVEUR = serveur

HEADER_SERVEUR = dir_serveur/includes/serveur.h

SRC_SERVEUR = \
dir_serveur/src/serveur_main.c \
dir_serveur/src/tools.c \
dir_serveur/src/serveur_init.c \
dir_serveur/src/client_connection.c \
dir_serveur/src/client_handling.c \
dir_serveur/src/serveur_main_loop.c

OBJ_SERVEUR = $(SRC_SERVEUR:.c=.o)

# ----- CLIENT

NAME_CLIENT = client

HEADER_CLIENT = dir_client/includes/client.h

SRC_CLIENT = dir_client/src/client_main.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# ------ LIB
DIR_LIB = ./libft/

# ----- Compilation command

CC = gcc -g -Wall -Werror -Wextra

# ----- Rules

all : Lib $(NAME_SERVEUR) $(NAME_CLIENT)

$(NAME_SERVEUR) : $(OBJ_SERVEUR)
	$(CC) -o $(NAME_SERVEUR) $(OBJ_SERVEUR) -L./libft/ -lft

$(NAME_CLIENT) : $(OBJ_CLIENT)
	$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) -L./libft/ -lft

Lib : 
	make -C $(DIR_LIB)

clean :
	rm -rf $(OBJ_SERVEUR) $(OBJ_CLIENT)
	cd $(DIR_LIB) ; make clean

fclean : clean
	rm -rf $(NAME_SERVEUR) rm -rf $(NAME_CLIENT)
	cd $(DIR_LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re