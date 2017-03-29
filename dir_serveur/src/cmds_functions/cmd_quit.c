/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:20:23 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 19:20:24 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void		cmd_quit(t_serveur *serv, t_client *client, char *msg,
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
		free_lexed_array(lexed_msg);
		return ;
	}
	else
	{
		send_msg(client, "$SERVMSG::Exiting server...\n");
		client->to_be_disconnected = 1;
	}
}
