/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels_list_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:46:13 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/28 15:46:17 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	High level usage function : client > chan.
*/

void	client_joins_chan(t_client *client, t_channel *chan)
{
	add_client_to_chan(chan, client);
	add_chan_to_list(&client->channels_joined, chan);
	client->current_channel = chan;
	client->nb_chan_joined += 1;
	send_msg(client, "$SERVMSG::Joined channel [");
	send_msg(client, chan->name);
	send_msg(client, "]\n");
}

/*
**	Stock channel into list of channel
**	Channel -> CHANNEL_LIST
**	WARNING: send address of pointer in first arg, or else you will have
**	copy/leaks problems.
*/

t_channel_list		*add_chan_to_list(t_channel_list **chan_list, t_channel *new_chan)
{
	t_channel_list		*tmp;
	t_channel_list		*new_node;

	new_node = (t_channel_list *)s_malloc(sizeof(t_channel_list));
	new_node->next = NULL;
	new_node->chan_ptr = new_chan;
	if (!(*chan_list))
	{
		*chan_list = new_node;
		return (new_node);
	}
	else
	{
		tmp = *chan_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		return (*chan_list);
	}
}

/*
**	Remove a channel node from a channel list. DOES NOT DELETE THE CHANNEL.
**	WARNING: send address of pointer in first arg, or else you will have
**	copy/leaks problems.
*/

void		remove_chan_from_list(t_channel_list **chan_list, t_channel *chan)
{
	t_channel_list		*tmp;
	t_channel_list		*tmp2;

	tmp = *chan_list;
	if (!tmp)
		return ;
	tmp2 = tmp->next;
	if (!tmp2 && tmp->chan_ptr == chan)
	{
		free(tmp);
		*chan_list = NULL;
		return ;
	}
	else
	{
		while (tmp2)
		{
			if (tmp2->chan_ptr == chan)
			{
				tmp->next = tmp2->next;
				free(tmp2);
				return ;
			}
			tmp = tmp2;
			if (tmp2)
				tmp2 = tmp2->next;
		}
	}
}
