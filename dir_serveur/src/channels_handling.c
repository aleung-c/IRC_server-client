/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:59:15 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/27 17:59:16 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	This function return a pointer to channel if the channel exists,
**	or NULL otherwise, searching by the name of the channel.
*/

t_channel		*get_channel(t_serveur *serv, char *chan_name)
{
	t_channel	*tmp;

	tmp = serv->channel_list;
	while (tmp)
	{
		if (ft_strncmp(chan_name, tmp->name, ft_strlen(tmp->name)) == 0
			&& ft_strlen(chan_name) == ft_strlen(tmp->name))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_channel	*create_new_chan(t_serveur *serv, char *chan_name)
{
	t_channel	*new_chan;
	t_channel	*tmp;

	new_chan = (t_channel *)malloc(sizeof(t_channel));
	ft_memcpy(new_chan->name, chan_name, ft_strlen(chan_name));
	new_chan->name[ft_strlen(chan_name)] = '\0';
	new_chan->connected_clients = NULL;
	new_chan->next = NULL;
	if (!serv->channel_list)
	{
		serv->channel_list = new_chan;
	}
	else
	{
		tmp = serv->channel_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_chan;
	}
	return (new_chan);
}

void	add_client_to_chan(t_channel *chan, t_client *client)
{
	t_client_list	*client_node;
	t_client_list	*tmp;

	client_node = (t_client_list *)malloc(sizeof(t_client_list));
	client_node->client_ptr = client;
	client_node->next = NULL;
	if (!chan->connected_clients)
	{
		chan->connected_clients = client_node;
		return ;
	}
	else
	{
		tmp = chan->connected_clients;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = client_node;
	}
}