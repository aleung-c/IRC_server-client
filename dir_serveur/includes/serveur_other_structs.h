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

# include "serveur.h"

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
	int						nb_clients;
	t_client_list			*connected_clients;
}							t_channel;

/*
** ----- Used to list channel on serv or on clients.
*/

typedef struct				s_channel_list
{
	t_channel				*chan_ptr;
	struct s_channel_list	*next;
}							t_channel_list;

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
** ----- sub container for client list (frankly, it was not needed)
*/

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
