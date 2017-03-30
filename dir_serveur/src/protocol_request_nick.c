/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_request_nick.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:00:42 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 14:00:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

void	protocol_request_nick(t_serveur *serv, t_client *client, char *msg,
								int proto_msg_delim_pos)
{
	char	**lexed_msg;

	(void)serv;
	lexed_msg = string_lexer(msg + proto_msg_delim_pos, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) > 1)
	{
		printf("[Server]: Invalid protocol format: [%s]\n",
			msg);
		send_msg(client, "$PROTOREQ::NICK::KO::Invalid protocol format"
							" for NICK request.\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return ;
	}
	else
	{
		printf("strlen: %d [0] = %c\n", (int)ft_strlen(lexed_msg[0]),
			(msg + proto_msg_delim_pos)[0]);
		if ((int)ft_strlen(lexed_msg[0]) > MAX_NICK_LEN)
		{
			printf("[Server]: Invalid protocol request: [%s]\n", msg);
			send_msg(client, "$PROTOREQ::NICK::KO::NICK protocol request"
							" ERROR: nickname too long.\n");
			free_lexed_array(lexed_msg);
			return ;
		}
		else
		{
			if (get_client_by_nick(serv, lexed_msg[0]))
			{
				printf("[Server]: NICK protocol request:"
					" nickname already taken: [%s]\n", msg);
				send_msg(client, "$PROTOREQ::NICK::KO::NICK protocol request"
								" ERROR: nickname already taken.\n");
				free_lexed_array(lexed_msg);
				return ;
			}
			ft_memcpy(client->nickname, lexed_msg[0], MAX_NICK_LEN);
			client->nickname[ft_strlen(lexed_msg[0])] = '\0';
			send_msg(client, "$PROTOREQ::NICK::OK::Nickname changed to: [");
			send_msg(client, lexed_msg[0]);
			send_msg(client, "]\n");
			free_lexed_array(lexed_msg);
			if (client->has_nick == 0)
			{
				send_msg(client, "$SERVMSG::\n");
				client->has_nick = 1;
				send_msg(client, "$SERVMSG::----- Now Join a channel with"
					" $JOIN::#default\n");
			}
		}
	}
 }
