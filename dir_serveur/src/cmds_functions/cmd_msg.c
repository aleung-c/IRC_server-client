/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:48:18 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 12:48:22 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void		cmd_msg(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char		**lexed_msg;
	t_client	*target_client;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) < 3)
	{
		printf("[Server]: Missing argument for /msg : [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Missing argument for /msg\n"
			"$PROMPT::\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return ;
	}
	else
	{
		if (ft_strlen(lexed_msg[1]) > MAX_NICK_LEN)
		{
			printf("[Server]: targeted nickname too long for /msg : [%s]\n",
				msg + user_msg_start);
			send_msg(client, "$ERRSERVMSG::targeted nickname too long"
							" for /msg\n");
			send_msg(client, "$PROMPT::\n");
			free_lexed_array(lexed_msg);
			return ;
		}
		if ((target_client = get_client_by_nick(serv, lexed_msg[1])))
		{
			send_msg(target_client, "$PRIVATEMSG::");
			send_msg(target_client, client->nickname);
			send_msg(target_client, "::");
			send_msg(target_client, msg + user_msg_start
				+ ft_strlen(lexed_msg[0]) + 1
				+ ft_strlen(lexed_msg[1]) + 1);
			send_msg(target_client, "\n$PROMPT::\n");
			send_msg(client, "$PRIVATEMSG::to > ");
			send_msg(client, target_client->nickname);
			send_msg(client, "::");
			send_msg(client, msg + user_msg_start
				+ ft_strlen(lexed_msg[0]) + 1
				+ ft_strlen(lexed_msg[1]) + 1);
			send_msg(client, "\n$PROMPT::\n");
		}
		else
		{
			printf("[Server]: targeted client not found for /msg : [%s]\n",
				msg + user_msg_start);
			send_msg(client, "$ERRSERVMSG::targeted client not found"
								"\n$PROMPT::\n");
		}
		free_lexed_array(lexed_msg);
	}
}