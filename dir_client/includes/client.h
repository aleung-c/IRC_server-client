/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:27:15 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:27:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include "../../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <time.h>
# include <netdb.h>

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

# define HOSTNAME_MAX_LEN 255

# define BUFFER_SIZE 4096
# define MSG_SIZE 512

# define PROTOCOL_MAX_MSG_SIZE 10
# define CMD_MAX_LEN 10

# define MSG_DELIM '\n'

# define MAX_NICK_LEN 9
# define MAX_CHANNEL_NAME_LEN 50
# define MAX_JOINABLE_CHAN 5
# define DEFAULT_NICK "aleung-c"
# define DEFAULT_CHAN "#default"

/*
**	Server structs.
*/

# include "client_other_structs.h"
# include "client_main_struct.h"

/*
** ----- Function prototypes
*/

/*
**	Init functions.
*/

void			init_client_vars(t_client *client);

int				input_args_handling(t_client *client, int argc, char **argv);
void			print_usage(char *arg);

int				connect_client(t_client *client);
int				try_client_connection(t_client *client);
int				client_connect_exec(t_client *client, struct protoent *proto);

int				get_hostname(t_client *client, char *arg);
int				get_port(t_client *client, char *arg);
int				check_port_format(char *arg);

void			close_connection(t_client *client);

/*
**	Main loop
*/

void			client_main_loop(t_client *client);
void			init_fd(t_client *client);
struct timeval	*set_select_timeout(struct timeval *t);
void			check_fd_sets(t_client *client);

/*
**	Socket reading/sending
*/

void			check_socket_io(t_client *client);
int				read_socket(t_client *client);
void			write_socket(t_client *client);

/*
**	user input handling
*/

void			read_user_input(t_client *client);
void			parse_user_connection_cmd(t_client *client,
					char *user_input_buffer);
void			user_input_error(char **lexed_msg, char *type, char *cmd);
void			parse_user_auth_msg(t_client *client, char *user_input);
void			parse_user_chat_msg(t_client *client, char *user_input);

/*
**	receveid msg handling
*/

void			process_receiveid_msg(t_client *client);
void			parse_auth_msg(t_client *client, char *msg);
void			auth_msg_nick_failed(t_client *client);
void			auth_msg_nick_success(t_client *client);
void			parse_regular_msg(t_client *client, char *msg);

/*
**	Displayin receveid msg
*/

void			display_public_msg(t_client *client, char *msg);
void			display_private_msg(t_client *client, char *msg);
void			display_error_msg(t_client *client, char *msg);
void			display_who_msg(t_client *client, char *msg);

/*
**	Circular buffer usage
*/

void			write_into_buffer(t_circular_buffer *buffer,
					char *str, int len);
int				get_buffer_space(t_circular_buffer *buffer);
void			clear_circular_buffer(t_circular_buffer *buffer);
char			*get_buffer_str(t_circular_buffer *buffer);

char			*extract_buffer_str(t_circular_buffer *buffer);
char			*get_buffer_delimstr(t_circular_buffer *buffer,
					int delim_count);
int				search_buffer_delim(t_circular_buffer *buffer);
char			*get_buffer_msg(t_circular_buffer *buffer);
void			send_msg(t_client *client, char *msg);
int				extract_datas_to_send(t_circular_buffer *buffer,
					char *send_buffer);

/*
**	tools
*/

void			*s_malloc(size_t size);
void			print_reception(char *msg);
void			print_sending(char *msg, int len);
void			replace_nl(char *str, int len);
int				get_len_to_delim(char *msg, char c);
int				len_to_next_proto_arg(char *msg);
void			put_prompt(void);

char			**string_lexer(char *msg, char delim);
int				str_word_count(char *msg, char delim);
void			fill_array(char **array, char *msg, char delim, int nb_words);
int				get_array_count(char **array);
void			turn_tabs_to_space(char *str);
void			turn_nl_to_zero(char *str);
void			free_lexed_array(char **array);

#endif
