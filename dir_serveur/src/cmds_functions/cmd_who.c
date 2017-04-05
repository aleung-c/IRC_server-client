/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:17:03 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 10:17:04 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void	cmd_who(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char	**lexed_msg;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (cmd_who_parse(lexed_msg, client, msg + user_msg_start) == -1)
		return ;
	if (!client->current_channel)
	{
		printf(KMAG "[Server]: No current channel for client #%d\n" KRESET,
			client->id);
		send_msg(client, "$ERRSERVMSG::No current channel,"
			" try to /join one!\n");
		free_lexed_array(lexed_msg);
		return ;
	}
	else
	{
		cmd_who_send_client_list(client, client->current_channel);
		free_lexed_array(lexed_msg);
	}
}

int		cmd_who_parse(char **lexed_msg, t_client *client, char *msg)
{
	if (!lexed_msg || get_array_count(lexed_msg) > 1)
	{
		printf("[Server]: Invalid arguments for /who command: [%s]\n", msg);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for command /who\n");
		free_lexed_array(lexed_msg);
		return (-1);
	}
	return (0);
}

void	cmd_who_send_client_list(t_client *client, t_channel *channel)
{
	t_client_list	*tmp;

	send_msg(client, "$SERVWHO::");
	send_msg(client, channel->name);
	send_msg(client, "::");
	tmp = channel->connected_clients;
	while (tmp)
	{
		send_msg(client, tmp->client_ptr->nickname);
		if (tmp->next)
			send_msg(client, "  ");
		tmp = tmp->next;
	}
	send_msg(client, "\n$PROMPT::\n");
}