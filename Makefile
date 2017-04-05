# ----- SERVEUR

NAME_SERVEUR = serveur

HEADER_SERVEUR = dir_serveur/includes/serveur.h

SRC_SERVEUR = \
dir_serveur/src/serveur_main.c \
dir_serveur/src/tools.c \
dir_serveur/src/tools_2.c \
dir_serveur/src/tools_parsing.c \
dir_serveur/src/serveur_init.c \
dir_serveur/src/serveur_init_cmds.c \
dir_serveur/src/client_connection.c \
dir_serveur/src/client_connection_msg.c \
dir_serveur/src/client_handling.c \
dir_serveur/src/client_nick_handling.c \
dir_serveur/src/client_input_handling.c \
dir_serveur/src/client_input_protocol_parsing.c \
dir_serveur/src/client_input_msg_parsing.c \
dir_serveur/src/client_simple_msg.c \
dir_serveur/src/client_input_cmd_parsing.c \
dir_serveur/src/socket_input_output.c \
dir_serveur/src/circular_buffer.c \
dir_serveur/src/circular_buffer_extraction.c \
dir_serveur/src/circular_buffer_sending.c \
dir_serveur/src/channels_handling.c \
dir_serveur/src/channels_list_handling.c \
dir_serveur/src/channels_clients_handling.c \
dir_serveur/src/protocol_request_nick.c \
dir_serveur/src/protocol_request_join.c \
dir_serveur/src/cmds_functions/cmd_nick.c \
dir_serveur/src/cmds_functions/cmd_join.c \
dir_serveur/src/cmds_functions/cmd_leave.c \
dir_serveur/src/cmds_functions/cmd_list.c \
dir_serveur/src/cmds_functions/cmd_who.c \
dir_serveur/src/cmds_functions/cmd_amsg.c \
dir_serveur/src/cmds_functions/cmd_msg.c \
dir_serveur/src/cmds_functions/cmd_quit.c \
dir_serveur/src/cmds_functions/cmd_exit.c \
dir_serveur/src/serveur_main_loop.c


OBJ_SERVEUR = $(SRC_SERVEUR:.c=.o)

# ----- CLIENT

NAME_CLIENT = client

HEADER_CLIENT = dir_client/includes/client.h

SRC_CLIENT = dir_client/src/client_main.c \
dir_client/src/input_arg_handling.c \
dir_client/src/circular_buffer.c \
dir_client/src/circular_buffer_sending.c \
dir_client/src/circular_buffer_extraction.c \
dir_client/src/client_connection.c \
dir_client/src/client_init.c \
dir_client/src/tools.c \
dir_client/src/tools_parsing.c \
dir_client/src/client_user_input_handling.c \
dir_client/src/client_socket_io.c \
dir_client/src/client_main_loop.c \
dir_client/src/process_received_msg.c \
dir_client/src/display_msg.c

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