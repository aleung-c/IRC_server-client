/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_input_protocol_parsing.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:23:10 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/27 15:23:12 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	If someone does not respect the protocol, he is disconnected.
**	That is what we check here.
*/

void	parse_client_protocol_msg(t_serveur *serv, t_client *client, char *msg)
{
	int		proto_msg_end_pos;

	if ((proto_msg_end_pos = get_protocol_msg_end_pos(msg)) != -1)
	{
		if (ft_strncmp(msg, "$MSG::", proto_msg_end_pos) == 0)
			parse_client_user_msg(serv, client, msg, proto_msg_end_pos);
		else if (ft_strncmp(msg, "$NICK::", proto_msg_end_pos) == 0)
			protocol_request_nick(serv, client, msg, proto_msg_end_pos + 1);
		else if (ft_strncmp(msg, "$JOIN::", proto_msg_end_pos) == 0)
		{
			if (client->has_nick == 0)
			{
				send_msg(client, "ERRSERVMSG::Client needs a $NICK:: first!");
				return ;
			}
			protocol_request_join(serv, client, msg, proto_msg_end_pos + 1);
		}
		else
			critical_protocol_error(client);
	}
	else
		critical_protocol_error(client);
}

void	protocol_auth_errmsg(t_client *client)
{
	printf(KMAG "[Server]: Client not authentified.\n" KRESET);
	send_msg(client, "$ERRSERVMSG::Authentify first with"
		" PROTOCOL '$NICK::aleung-c' then '$JOIN::#default'\n");
	return ;
}

void	critical_protocol_error(t_client *client)
{
	printf(KMAG "[Server]: Not a protocol msg! - [client #%d sock %d]\n"
			KRESET, client->id, client->sock);
	send_msg(client, KRED "[Server]: CRITICAL PROTOCOL ERROR -"
		" Not a protocol input: Unauthorized client." KRESET);
	send_msg(client, "\n---- Closing connection ----\n");
	client->to_be_disconnected = 1;
}

/*
**	In my protocol, msg between server and client
**	must have this form: [$MSG::XXXX\n]
**	Everything following the :: will be the user input.
*/

int		get_protocol_msg_end_pos(char *msg)
{
	int			i;

	i = 0;
	if (!msg[i] || msg[i] != '$')
		return (-1);
	while (msg[i] && i < PROTOCOL_MAX_MSG_SIZE)
	{
		if (msg[i] && msg[i] == ':' && msg[i + 1] && msg[i + 1] == ':')
			return (i + 1);
		i++;
	}
	return (-1);
}
