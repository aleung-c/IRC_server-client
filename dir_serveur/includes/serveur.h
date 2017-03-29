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
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

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
# define MSG_SIZE 512 // default 512

# define MSG_DELIM '\n'

# define PROTOCOL_MAX_MSG_SIZE 10
# define CMD_MAX_LEN 10
# define PRIV_MSG_DEST_MAX_LEN 9
# define TEXT_MSG_MAX_LEN 400 // 512 - 10 - 10 - 10 ....

/*
**	Server parsing defines
*/

# define NB_OF_CMDS 9


/*
**	Server irc define
*/

# define MAX_NICK_LEN 9
# define MAX_CHANNEL_NAME_LEN 50
# define MAX_JOINABLE_CHAN 5


/*
**	Server structs.
*/

# include "serveur_types.h"
# include "serveur_other_structs.h"
# include "serveur_main_struct.h"

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
** serveur_init_cmds.c
*/

void						init_cmd_list(t_serveur *serv);

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
void						new_client_auth_request(t_client *client);
void						new_client_auth_welcome(t_client *client);

/*
** client_handling.c
*/

t_client					*create_new_client(t_serveur *serv, int c_sock);
void						set_new_client(t_serveur *serv,
								t_client *new_client);
void						add_client_to_list(t_serveur *serv,
								t_client *new_client);
void						client_disconnect(t_serveur *serv,
								t_client *client);
void						clear_client_variables(t_client *client);
void						remove_client_from_list(t_serveur *serv,
								t_client *client);
t_client					*get_client_by_nick(t_serveur *serv, char *nick);

/*
** socket_input_output.c
*/

void						check_sockets_io(t_serveur *serv);
int							read_client_socket(t_serveur *serv,
								t_client *client);
void						write_client_socket(t_serveur *serv,
								t_client *client);

/*
** ---- Entry point to client process - client_input_handling.c
*/

void						process_clients_inputs(t_serveur *serv);

/*
** client_input_protocol_parsing.c
*/

void						parse_client_protocol_msg(t_serveur *serv,
								t_client *client, char *msg);
int							get_protocol_msg_end_pos(char *msg);

void						protocol_auth_errmsg(t_client *client);

/*
** protocol requests.
*/

void						protocol_request_nick(t_serveur *serv,
								t_client *client, char *msg,
								int proto_msg_delim_pos);
void						protocol_request_join(t_serveur *serv,
								t_client *client, char *msg,
								int proto_msg_delim_pos);
int							protocol_join_request_parsing(char **lexed_msg,
								t_client *client, char *msg,
								int proto_msg_delim_pos);

/*
** client_input_msg_parsing.c
*/

void						parse_client_user_msg(t_serveur *serv,
								t_client *client, char *msg, int msg_start);

/*
**	Send simple msg
*/

void						send_simple_chat_msg(t_serveur *serv,
								t_client *client, char *msg,
								int msg_start);
void						send_msg_to_chan_users(t_channel *chan,
								t_client *client_sender, char *msg);

/*
** client_input_cmd_parsing.c
*/

void						parse_client_chat_cmd(t_serveur *serv,
								t_client *client, char *msg, int msg_start);

/*
** circular_buffer.c
*/

void						write_into_buffer(t_circular_buffer *buffer,
								char *received, int len);
int							get_buffer_space(t_circular_buffer *buffer);
void						clear_circular_buffer(t_circular_buffer *buffer);
char						*get_buffer_str(t_circular_buffer *buffer);
char						*get_buffer_delimstr(t_circular_buffer *buffer,
								int delim_count);
int							search_buffer_delim(t_circular_buffer *buffer);
char						*get_buffer_msg(t_circular_buffer *buffer);
int							extract_datas_to_send(t_circular_buffer *buffer,
								char *send_buffer);
void						send_msg(t_client *client, char *msg);

/*
**	Chat commands
*/

void						cmd_nick(t_serveur *serv,
								t_client *client, char *msg,
								int user_msg_start);
void						cmd_join(t_serveur *serv, t_client *client,
								char *msg, int user_msg_start);
int							cmd_join_parse_args(char **lexed_msg,
								t_client *client, char *msg,
								int user_msg_start);
void						cmd_leave(t_serveur *serv, t_client *client,
								char *msg, int user_msg_start);
int							cmd_leave_parse_arg(char **lexed_msg,
								t_client *client, char *msg,
								int user_msg_start);
void						cmd_who(t_serveur *serv, t_client *client,
								char *msg, int user_msg_start);
void						cmd_who_send_client_list(t_client *client,
								t_channel *channel);
void						cmd_list(t_serveur *serv, t_client *client,
								char *msg, int user_msg_start);
void						cmd_list_sending(t_serveur *serv, t_client *client);
void						cmd_amsg(t_serveur *serv, t_client *client,
								char *msg, int user_msg_start);
void						cmd_amsg_sending(t_client *client, char *msg);
void						cmd_msg(t_serveur *serv, t_client *client, char *msg,
								int user_msg_start);
void						cmd_quit(t_serveur *serv, t_client *client, char *msg,
								int user_msg_start);

/*
**	Channel Handling
*/

t_channel					*get_chan_from_list(t_channel_list *list,
								char *chan_name);
t_channel					*create_new_chan(t_serveur *serv,
								char *chan_name);

/*
**	Channel list Handling
*/

t_channel_list				*add_chan_to_list(t_channel_list **chan_list,
								t_channel *new_chan);
void						remove_chan_from_list(t_channel_list **chan_list,
								t_channel *chan);


/*
**	Channel client Handling
*/
void						add_client_to_chan(t_channel *chan,
								t_client *client);
void						remove_client_from_chan(t_channel *chan, t_client *client);

/*
** tools.c
*/

void						ft_printfstr(char *format, void *arg);
void						*s_malloc(size_t size);
void						print_reception(char *msg, t_client *client);
void						print_sending(char *msg, t_client *client, int len);
void						replace_nl(char *str, int len);
int							get_len_to_delim(char *msg, char c);

char						**string_lexer(char *msg, char delim);
int							str_word_count(char *msg, char delim);
void						fill_array(char **array, char *msg, char delim, int nb_words);
int							get_array_count(char **array);
void						turn_tabs_to_space(char *str);
void						turn_nl_to_zero(char *str);
void						free_lexed_array(char **array);

#endif
