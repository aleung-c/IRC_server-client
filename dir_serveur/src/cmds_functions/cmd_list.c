/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:19:07 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 11:19:08 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void	cmd_list(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char	**lexed_msg;

	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) > 1)
	{
		printf("[Server]: Invalid arguments for /list command: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for command /list\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return ;
	}
	free_lexed_array(lexed_msg);
	if (!serv->channel_list)
	{
		printf(KMAG "[Server]: No channel opened on the server%d\n" KRESET,
			client->id);
		send_msg(client, "$ERRSERVMSG::No channel opened on the server,"
			" create one with /join !\n");
		return ;
	}
	else
	{
		cmd_list_sending(serv, client);
	}
}

void	cmd_list_sending(t_serveur *serv, t_client *client)
{
	t_channel_list	*tmp;

	tmp = serv->channel_list;
	send_msg(client, "$SERVMSG::Channel List:\n");
	send_msg(client, "$SERVMSG::");
	while (tmp)
	{
		send_msg(client, tmp->chan_ptr->name);
		if (tmp->next)
			send_msg(client, " ");
		tmp = tmp->next;
	}
	send_msg(client, "\n");
}