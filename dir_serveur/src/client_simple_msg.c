/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_simple_msg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 09:50:57 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 09:50:59 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	If a client send $MSG:: and not '/' is following, I consider that
**	this is a simple msg to be sent to the current channel.
**	See /amsg to send to all channels. 
*/

void	send_simple_chat_msg(t_serveur *serv, t_client *client, char *msg,
								int msg_start)
{
	(void)serv;
	if (ft_strlen(msg + msg_start) > TEXT_MSG_MAX_LEN)
	{
		printf(KMAG "[Server]: Chat message too long: [%.*s...]\n" KRESET,
			TEXT_MSG_MAX_LEN / 2, msg + msg_start);
		send_msg(client, "$ERRSERVMSG::Chat message too long.\n");
	}
	else
	{
		if (client->current_channel)
		{
			send_msg_to_chan_users(client->current_channel, client, msg +
				msg_start);
		}
		else
		{
			printf(KMAG "[Server]: No current channel for client #%d: [%.*s...]\n" KRESET,
				client->id, TEXT_MSG_MAX_LEN / 2, msg + msg_start);
			send_msg(client, "$ERRSERVMSG::No current channel to send"
				"messages, try to /join one!\n");
			return ;
		}
	}
}

/*
**	Key function for sending msg. Sends message to all user connected to the
**	given channel.
*/

void	send_msg_to_chan_users(t_channel *chan, t_client *client_sender,
									char *msg)
{
	t_client_list	*tmp;

	if (chan)
	{
		tmp = chan->connected_clients;
		while (tmp)
		{
			send_msg(tmp->client_ptr, "$PUBLICMSG::");
			send_msg(tmp->client_ptr, chan->name);
			send_msg(tmp->client_ptr, "::");
			send_msg(tmp->client_ptr, client_sender->nickname);
			send_msg(tmp->client_ptr, "::");
			send_msg(tmp->client_ptr, msg);
			send_msg(tmp->client_ptr, "\n");
			send_msg(tmp->client_ptr, "$PROMPT::\n");
			tmp = tmp->next;
		}
	}
}