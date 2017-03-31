/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_amsg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:13:00 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 12:13:01 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void		cmd_amsg(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char	**lexed_msg;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) < 2)
	{
		printf("[Server]: Missing argument for /amsg : [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Missing argument for /amsg\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return ;
	}
	else
	{
		if (!client->channels_joined)
		{
			printf(KMAG "[Server]: No channel for client #%d: [%.*s...]\n"
				KRESET, client->id, TEXT_MSG_MAX_LEN / 2, msg + user_msg_start);
			send_msg(client, "$ERRSERVMSG::No channels to send"
				" messages, try to /join one!\n");
		}
		else
		{
			cmd_amsg_sending(client, msg + user_msg_start
				+ ft_strlen(lexed_msg[0]) + 1);
		}
		free_lexed_array(lexed_msg);
	}
}

void		cmd_amsg_sending(t_client *client, char *msg)
{
	t_channel_list		*channel_tmp;
	t_client_list		*client_tmp;

	channel_tmp = client->channels_joined;
	while (channel_tmp)
	{
		client_tmp = channel_tmp->chan_ptr->connected_clients;
		while (client_tmp)
		{
			send_msg(client_tmp->client_ptr, "$PUBLICMSG::");
			send_msg(client_tmp->client_ptr, channel_tmp->chan_ptr->name);
			send_msg(client_tmp->client_ptr, "::");
			send_msg(client_tmp->client_ptr, client->nickname);
			send_msg(client_tmp->client_ptr, "::");
			send_msg(client_tmp->client_ptr, msg);
			send_msg(client_tmp->client_ptr, "\n");
			client_tmp = client_tmp->next;
		}
		channel_tmp = channel_tmp->next;
	}
}