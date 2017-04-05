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

t_channel		*get_chan_from_list(t_channel_list *list, char *chan_name)
{
	t_channel_list	*tmp;

	tmp = list;
	if (!chan_name || !list)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(chan_name, tmp->chan_ptr->name,
			ft_strlen(tmp->chan_ptr->name)) == 0
			&& ft_strlen(chan_name) == ft_strlen(tmp->chan_ptr->name))
		{
			return (tmp->chan_ptr);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	create a new channel and adds it to the server's channel list.
*/

t_channel		*create_new_chan(t_serveur *serv, char *chan_name)
{
	t_channel	*new_chan;

	new_chan = (t_channel *)malloc(sizeof(t_channel));
	ft_memcpy(new_chan->name, chan_name, ft_strlen(chan_name));
	new_chan->name[ft_strlen(chan_name)] = '\0';
	new_chan->connected_clients = NULL;
	new_chan->nb_clients = 0;
	add_chan_to_list(&(serv->channel_list), new_chan);
	printf(KCYN "[Server]: Created new channel [%s]\n" KRESET,
		new_chan->name);
	return (new_chan);
}

/*
**	When channel is taken down, free list of clients.
*/

void			clear_channel_clients(t_channel *chan)
{
	t_client_list	*tmp;
	t_client_list	*tmp2;

	if (chan->nb_clients == 1)
	{
		free(chan->connected_clients);
	}
	else if (chan->nb_clients > 1)
	{
		tmp = chan->connected_clients;
		tmp2 = tmp->next;
		while (tmp2->next)
		{
			free(tmp);
			tmp2 = tmp2->next;
		}
		free(tmp2);
	}
}

int				chan_has_forbidden_chars(char *chan_name)
{
	int i;

	i = 0;
	while (chan_name[i])
	{
		if (ft_isalnum(chan_name[i]) != 1
			&& chan_name[i] != '-'
			&& chan_name[i] != '_'
			&& chan_name[i] != '#')
			return (1);
		i++;
	}
	return (0);
}
