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

	lexed_msg = string_lexer(msg + proto_msg_delim_pos, ' ');
	if (proto_req_nick_parsing(lexed_msg, client, msg) == -1)
		return ;
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
		exec_nick_proto_request(lexed_msg, client);
		free_lexed_array(lexed_msg);
	}
}

int		proto_req_nick_parsing(char **lexed_msg, t_client *client, char *msg)
{
	if (!lexed_msg || get_array_count(lexed_msg) > 1
		|| nick_has_forbidden_chars(lexed_msg[0]) == 1)
	{
		printf("[Server]: Invalid protocol format: [%s]\n",
			msg);
		send_msg(client, "$PROTOREQ::NICK::KO::Invalid protocol format"
							" for NICK request.\n");
		if (lexed_msg)
			free_lexed_array(lexed_msg);
		return (-1);
	}
	else if ((int)ft_strlen(lexed_msg[0]) > MAX_NICK_LEN)
	{
		printf("[Server]: Invalid protocol request: [%s]\n", msg);
		send_msg(client, "$PROTOREQ::NICK::KO::NICK protocol request"
						" ERROR: nickname too long.\n");
		free_lexed_array(lexed_msg);
		return (-1);
	}
	return (0);
}

void	exec_nick_proto_request(char **lexed_msg, t_client *client)
{
	ft_memcpy(client->nickname, lexed_msg[0], MAX_NICK_LEN);
	client->nickname[ft_strlen(lexed_msg[0])] = '\0';
	send_msg(client, "$PROTOREQ::NICK::OK::Nickname changed to: [");
	send_msg(client, lexed_msg[0]);
	send_msg(client, "]\n");
	if (client->has_nick == 0)
	{
		send_msg(client, "$SERVMSG::\n");
		client->has_nick = 1;
		send_msg(client, "$SERVMSG::----- Now Join a channel with"
			" $JOIN::#default\n");
	}
}
