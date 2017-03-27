/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_other_structs.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:15:39 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/25 19:15:40 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVEUR_OTHER_STRUCTS_H
# define SERVEUR_OTHER_STRUCTS_H

/*
** ----- Used to list client in a channel.
*/

typedef struct				s_client_list
{
	t_client				*client_ptr;
	struct s_client_list	*next;
}							t_client_list;

/*
** ----- Channel
*/

typedef struct				s_channel
{
	char					name[MAX_CHANNEL_NAME_LEN];
	t_client_list			*connected_clients;

	struct s_channel		*next;
}							t_channel;

/*
** ----- Circular buffer
*/

typedef struct				s_circular_buffer
{
	int						is_waiting;
	char					data[BUFFER_SIZE];
	int						start;
	int						end;
	int						len;
}							t_circular_buffer;

/*
** ----- Client struct
*/

typedef struct				s_client
{
	int						sock;
	int						id;
	char					nickname[MAX_NICK_LEN + 1];

	t_channel				*current_channel;
	t_channel				*channels_joined[MAX_JOINABLE_CHAN];
	int						nb_chan_joined;

	t_circular_buffer		recv_buffer;
	t_circular_buffer		write_buffer;

	int						to_be_disconnected;

	struct s_client			*next;
}							t_client;

typedef struct				s_client_handler
{
	int						nb_clients;
	t_client				*clients_list;
}							t_client_handler;

/*
** ----- commands
*/

typedef	struct				s_chat_cmd
{
	char					*name;
	void					(*function)(t_serveur *serv,
								struct s_client *client, char *msg,
								int user_msg_start);
}							t_chat_cmd;

#endif