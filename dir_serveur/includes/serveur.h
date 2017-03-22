/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:08:03 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:17:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include "../../libft/libft.h"
# include <stdio.h> //
# include <unistd.h>

# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <time.h>

/*
**	color in text;
*/

# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"
# define KRESET "\x1B[0m"

/*
**	Boolean defines
*/

# define B_TRUE 1
# define B_FALSE 0

/*
**	Communication defines
*/

# define LISTEN_MAX_CLIENTS 10

# define BUFFER_SIZE 4096
# define MSG_SIZE 4096

# define ENDLINE "\n"

/*
** ----- Client struct
*/

typedef struct				s_channel
{
	int						nb;
	char					*name;
}							t_channel;

typedef struct				s_client
{
	int						sock;
	int						id;
	char					nickname[10];
	int						current_chan;

	struct s_client			*next;

}							t_client;

typedef struct				s_client_handler
{
	int						nb_clients;
	t_client				*clients_list;

}							t_client_handler;

/*
** ----- Serveur Main Struct -----
*/

typedef struct				s_serveur
{
	int						port;
	int						is_running;
	
	int						serveur_sock;
	int						sock_endpoint;

	fd_set					*read_fd_set;
	fd_set					*write_fd_set;

	t_client_handler		client_handler;
}							t_serveur;

/*
** ----- Functions prototypes -----
*/

/*
** serveur_main.c
*/

int							main(int argc, char **argv);
void						print_usage(char *arg);
/*
** serveur_init.c
*/

int							init_serveur(t_serveur *serv);
int							init_serveur_connection(t_serveur *serv);
int							init_error(char *error_source);
void						clear_serveur(t_serveur *serv);
void						print_serveur_datas(t_serveur *serv);

/*
** serveur_main_loop.c
*/

void						serveur_main_loop(t_serveur *serv);
void						init_fd(t_serveur *serv);
struct timeval				*set_select_timeout(struct timeval *t);
void						check_fd_sets(t_serveur *serv);

/*
** client_connection.c
*/

int							accept_connection(t_serveur *serv);
void						new_client_connection(t_serveur *serv);

/*
** client_handling.c
*/

t_client					*create_new_client(t_serveur *serv, int c_sock);
void						set_new_client(t_serveur *serv, t_client *new_client);
void						add_client_to_list(t_serveur *serv, t_client *new_client);

/*
** tools.c
*/

// int							ft_strlen(char *str);
void						ft_printfstr(char *format, char *msg);
// int							ft_atoi(const char *str);
// int							ft_isdigit(int c);
// void							ft_putchar(char c);
// void							ft_putnbr(int n);
void						*s_malloc(size_t size);

#endif
