/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_leave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:32:59 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/28 16:33:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

/*
**	TODO: Delete players from chans when leaving. etc etc.
*/

void		cmd_leave(t_serveur *serv, t_client *client, char *msg,
						int user_msg_start)
{
	char		**lexed_msg;
	t_channel	*channel;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if ((cmd_leave_parse_arg(lexed_msg, client, msg, user_msg_start)) == -1)
		return ;
	if (get_array_count(lexed_msg) == 1)
	{
		printf("[Server]: Leaving all channels\n");
		send_msg(client, "$SERVMSG::Leaving all channels\n");
		send_msg(client, "$PROMPT::\n");
		leave_all_chans(client);
		return ;
	}
	if (!(channel = get_chan_from_list(client->channels_joined,
			lexed_msg[1])))
	{
		printf(KMAG "[Server]: Channel to leave not found: [%s]\n" KRESET,
			lexed_msg[1]);
		send_msg(client, "$ERRSERVMSG::Channel to /leave not found.\n");
		return ;
	}
	else
	{
		leave_one_chan(client, channel);
	}
	free_lexed_array(lexed_msg);
}

int		cmd_leave_parse_arg(char **lexed_msg, t_client *client, char *msg,
							int user_msg_start)
{
	int		error;

	error = 0;
	if (!lexed_msg || get_array_count(lexed_msg) > 2)
	{
		printf("[Server]: Invalid arguments for leave command: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for /leave\n");
		send_msg(client, "$PROMPT::\n");
		error = -1;
	}
	else if (lexed_msg[1] && ft_strlen(lexed_msg[1]) > MAX_CHANNEL_NAME_LEN)
	{
		printf("[Server]: Channel name too long(%d char max): [%s]\n",
			MAX_CHANNEL_NAME_LEN, msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Channel name too long for /leave\n");
		send_msg(client, "$PROMPT::\n");
		error = -1;
	}
	if (lexed_msg && error == -1)
		free_lexed_array(lexed_msg);
	return (error);
}

void	leave_all_chans(t_client *client)
{
	t_channel_list	*tmp;

	tmp = client->channels_joined;
	while (tmp)
	{
		printf("hey2\n");
		leave_one_chan(client, tmp->chan_ptr);
		printf("hey3\n");
		tmp = tmp->next;
	}
}

void	leave_one_chan(t_client *client, t_channel *channel)
{
	remove_chan_from_list(&client->channels_joined, channel);
	remove_client_from_chan(channel, client);
	client->nb_chan_joined -= 1;
	send_msg(client, "$SERVMSG::left channel [");
	send_msg(client, channel->name);
	send_msg(client, "]\n");
	send_msg(client, "$PROMPT::\n");
	if (channel == client->current_channel)
	{
		if (client->channels_joined)
			client->current_channel = client->channels_joined->chan_ptr;
		else
			client->current_channel = NULL;
	}
}
