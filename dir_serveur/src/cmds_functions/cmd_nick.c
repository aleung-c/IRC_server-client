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
	if (!lexed_msg || get_array_count(lexed_msg) != 2)
	{
		printf("[Server]: Invalid arguments for nickname command: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for command /nick\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return ;
	}
	if (ft_strlen(lexed_msg[1]) > MAX_NICK_LEN)
	{
		printf("[Server]: Nickname too long(%d char max): [%s]\n",
			MAX_NICK_LEN, msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Nickname too long for command /nick\n");
		free_lexed_array(lexed_msg);
		return ;
	}
	ft_memcpy(client->nickname, lexed_msg[1], MAX_NICK_LEN);
	client->nickname[ft_strlen(lexed_msg[1])] = '\0';
	send_msg(client, "$SERVMSG::Nickname changed to: [");
	send_msg(client, lexed_msg[1]);
	send_msg(client, "]\n");
	free_lexed_array(lexed_msg);
}
