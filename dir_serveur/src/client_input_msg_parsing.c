/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_input_msg_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:23:20 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/27 15:23:23 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

void	parse_client_user_msg(t_serveur *serv, t_client *client,
								char *msg, int msg_start)
{
	(void)serv;
	(void)client;
	msg_start++;
	if (msg[msg_start] && msg[msg_start] == '/')
	{
		printf(KGRN "[Server]: user chat command will be parsed: %s\n"
			KRESET, &msg[msg_start]);
		parse_client_chat_cmd(serv, client, msg, msg_start);
	}
	else if (msg[msg_start])
	{
		printf(KGRN "[Server]: user chat message will be treated: %s\n"
			KRESET, &msg[msg_start]);
		send_simple_chat_msg(serv, client, msg, msg_start);
	}
	else
	{
		send_msg(client, "$PROMPT::\n");
	}
}
