/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:10:18 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/25 19:10:19 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void	cmd_nick(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char **lexed_msg;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (cmd_nick_parse_args(lexed_msg, client, msg + user_msg_start) == -1)
	{
		return ;
	}
	ft_memcpy(client->nickname, lexed_msg[1], MAX_NICK_LEN);
	client->nickname[ft_strlen(lexed_msg[1])] = '\0';
	send_msg(client, "$SERVMSG::Nickname changed to: [");
	send_msg(client, lexed_msg[1]);
	send_msg(client, "]\n$PROMPT::\n");
	free_lexed_array(lexed_msg);
}

int		cmd_nick_parse_args(char **lexed_msg, t_client *client, char *msg)
{
	if (!lexed_msg || get_array_count(lexed_msg) != 2)
	{
		printf("[Server]: Invalid arguments for nickname command: [%s]\n",
				msg);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for command /nick\n");
		send_msg(client, "$PROMPT::\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return (-1);
	}
	if (ft_strlen(lexed_msg[1]) > MAX_NICK_LEN)
	{
		printf("[Server]: Nickname too long(%d char max): [%s]\n",
			MAX_NICK_LEN, msg);
		send_msg(client, "$ERRSERVMSG::Nickname too long for command /nick\n");
		send_msg(client, "$PROMPT::\n");
		free_lexed_array(lexed_msg);
		return (-1);
	}
	if (nick_has_forbidden_chars(lexed_msg[1]) == 1)
	{
		send_msg(client, "$ERRSERVMSG::Invalid nickname\n$PROMPT::\n");
		return (-1);
	}
	return (0);
}
