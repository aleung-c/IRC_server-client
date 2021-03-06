/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:09:08 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/22 18:09:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	initialize a new client on the server
*/

t_client	*create_new_client(t_serveur *serv, int c_sock)
{
	t_client	*new_client;

	new_client = (t_client *)s_malloc(sizeof(t_client));
	new_client->next = NULL;
	new_client->sock = c_sock;
	set_new_client(serv, new_client);
	add_client_to_list(serv, new_client);
	serv->client_handler.nb_clients += 1;
	return (new_client);
}

/*
**	We set that new client base values.
*/

void		set_new_client(t_serveur *serv, t_client *new_client)
{
	new_client->id = serv->client_handler.nb_clients;
	ft_memset(new_client->nickname, 0, 10);
	new_client->current_channel = NULL;
	new_client->channels_joined = NULL;
	new_client->nb_chan_joined = 0;
	new_client->has_nick = 0;
	new_client->is_authentified = 0;
	new_client->to_be_disconnected = 0;
	clear_circular_buffer(&new_client->recv_buffer);
	clear_circular_buffer(&new_client->write_buffer);
}

/*
**	we put that new client in our client list.
*/

void		add_client_to_list(t_serveur *serv, t_client *new_client)
{
	t_client	*tmp;

	if (serv->client_handler.clients_list == NULL)
	{
		serv->client_handler.clients_list = new_client;
		return ;
	}
	else
	{
		tmp = serv->client_handler.clients_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_client;
		return ;
	}
}

/*
**	Remove client from server's global list.
**	see remove_client_from_chan() for the channel equivalent.
*/

void		remove_client_from_list(t_serveur *serv, t_client *client)
{
	t_client	*current;
	t_client	*prev;

	if (serv->client_handler.clients_list == client)
	{
		serv->client_handler.clients_list = client->next;
		free(client);
		serv->client_handler.nb_clients -= 1;
		return ;
	}
	prev = serv->client_handler.clients_list;
	current = serv->client_handler.clients_list->next;
	while (current && current != client)
	{
		prev = current;
		current = current->next;
	}
	if (!current || current != client)
	{
		printf("remove_client(): client not found\n");
		return ;
	}
	prev->next = client->next;
	free(client);
	serv->client_handler.nb_clients -= 1;
}
