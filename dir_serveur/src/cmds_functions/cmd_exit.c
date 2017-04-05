/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 15:31:46 by aleung-c          #+#    #+#             */
/*   Updated: 2017/04/05 15:31:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void	cmd_exit(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char		**lexed_msg;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) != 1)
	{
		printf("[Server]: Invalid arguments for exit command: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for exit\n");
		send_msg(client, "$PROMPT::\n");
	}
	else
	{
		send_msg(client, "$SERVMSG::Exiting server...\n");
		send_msg(client, "$EXITMSG::\n");
		client->to_be_disconnected = 1;
	}
	free_lexed_array(lexed_msg);
}
