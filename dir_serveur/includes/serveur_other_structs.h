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
** ----- Channel
*/

typedef struct				s_channel
{
	char					*name;

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
	char					nickname[10];
	int						current_chan;

	t_channel				*channels_joined;

	t_circular_buffer		recv_buffer;
	t_circular_buffer		write_buffer;

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
								struct s_client *client, char *arg);
}							t_chat_cmd;

#endif