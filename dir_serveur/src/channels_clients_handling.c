/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels_clients_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 09:23:46 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 09:23:47 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	Stock client pointer into channel list of clients
**	CLIENT -> CHANNEL_CLIENT_LIST
*/

void			add_client_to_chan(t_channel *chan, t_client *client)
{
	t_client_list	*new_client_node;
	t_client_list	*tmp;

	new_client_node = (t_client_list *)s_malloc(sizeof(t_client_list));
	new_client_node->client_ptr = client;
	new_client_node->next = NULL;
	chan->nb_clients += 1;
	if (!chan->connected_clients)
	{
		chan->connected_clients = new_client_node;
		return ;
	}
	else
	{
		tmp = chan->connected_clients;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_client_node;
	}
}

/*
**	Remove client from channel's list of client.
**	Does not free the client, but the node containing it.
**	-> listing purpose.
*/

void			remove_client_from_chan(t_channel *chan, t_client *client)
{
	t_client_list	*tmp;
	t_client_list	*tmp2;

	tmp = chan->connected_clients;
	if (!tmp)
		return ;
	else if (tmp->client_ptr == client)
	{
		free(tmp);
		chan->connected_clients = NULL;
		chan->nb_clients -= 1;
		return ;
	}
	else
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp2->client_ptr == client)
			{
				tmp->next = tmp2->next;
				chan->nb_clients -= 1;
				return ;
			}
			tmp = tmp2;
			if (tmp2)
				tmp2 = tmp2->next;
		}
	}
}