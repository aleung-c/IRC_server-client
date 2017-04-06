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

/*
**	/msg <target> <hello message etc>
*/

void		cmd_msg(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char		**lexed_msg;

	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (cmd_msg_parsing(lexed_msg, client, msg, user_msg_start) == -1)
	{
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return ;
	}
	cmd_msg_try_exec(serv, lexed_msg, client, msg + user_msg_start);
	free_lexed_array(lexed_msg);
}

int			cmd_msg_parsing(char **lexed_msg, t_client *client, char *msg,
					int user_msg_start)
{
	if (!lexed_msg || get_array_count(lexed_msg) < 3)
	{
		printf("[Server]: Missing argument for /msg : [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Missing argument for /msg\n$PROMPT::\n");
		return (-1);
	}
	if (ft_strlen(lexed_msg[1]) > MAX_NICK_LEN)
	{
		printf("[Server]: targeted nickname too long for /msg : [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::targeted nickname too long"
						" for /msg\n$PROMPT::\n");
		return (-1);
	}
	if (ft_strlen(msg + user_msg_start
		+ ft_strlen(lexed_msg[0])
		+ ft_strlen(lexed_msg[1])) > TEXT_MSG_MAX_LEN)
	{
		printf("[Server]: message too long for /msg : [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::message too long for /msg\n$PROMPT::\n");
		return (-1);
	}
	return (0);
}

void		cmd_msg_try_exec(t_serveur *serv, char **lexed_msg,
								t_client *client, char *msg)
{
	t_client	*target_client;

	if ((target_client = get_client_by_nick(serv, lexed_msg[1])))
	{
		cmd_msg_sending(lexed_msg, client, target_client, msg);
	}
	else
	{
		printf("[Server]: targeted client not found for /msg : [%s]\n", msg);
		send_msg(client, "$ERRSERVMSG::targeted client not found"
							"\n$PROMPT::\n");
	}
}

void		cmd_msg_sending(char **lexed_msg, t_client *client,
							t_client *target_client, char *msg)
{
	send_msg(target_client, "$PRIVATEMSG::");
	send_msg(target_client, client->nickname);
	send_msg(target_client, "::");
	send_msg(target_client, msg + ft_strlen(lexed_msg[0]) + 1
		+ ft_strlen(lexed_msg[1]) + 1);
	send_msg(target_client, "\n$PROMPT::\n");
	send_msg(client, "$PRIVATEMSG::to > ");
	send_msg(client, target_client->nickname);
	send_msg(client, "::");
	send_msg(client, msg + ft_strlen(lexed_msg[0]) + 1
		+ ft_strlen(lexed_msg[1]) + 1);
	send_msg(client, "\n$PROMPT::\n");
}
