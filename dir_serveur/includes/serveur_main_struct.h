/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_main_struct.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:13:46 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/25 19:13:47 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_MAIN_STRUCT_H
# define SERVEUR_MAIN_STRUCT_H

# include "serveur.h"

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

	t_channel_list			*channel_list;
	t_chat_cmd				*chat_cmd_table;

	t_client_handler		client_handler;
}							t_serveur;

/*
** ----- Client struct
*/

typedef struct				s_client
{
	int						sock;
	int						id;
	char					nickname[MAX_NICK_LEN_P1];

	t_channel				*current_channel;
	t_channel_list			*channels_joined;
	int						nb_chan_joined;

	t_circular_buffer		recv_buffer;
	t_circular_buffer		write_buffer;

	int						has_nick;
	int						is_authentified;
	int						to_be_disconnected;

	struct s_client			*next;
}							t_client;

#endif
