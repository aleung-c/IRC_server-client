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

	(void)serv;
	if ((proto_msg_end_pos = get_protocol_msg_end_pos(msg)) != -1)
	{
		if (ft_strncmp(msg, "$MSG::", proto_msg_end_pos) == 0)
		{
			if (client->is_authentified == 1)
			{
				printf(KGRN "[Server]: MSG received will be treated.\n" KRESET);
				parse_client_user_msg(serv, client, msg, proto_msg_end_pos);
			}
			else
				protocol_auth_errmsg(client);
		}
		else if (ft_strncmp(msg, "$NICK::", proto_msg_end_pos) == 0)
		{
			printf(KGRN "[Server]: NICK PROTOCOL request received will be treated.\n" KRESET);
			protocol_request_nick(serv, client, msg, proto_msg_end_pos + 1);
		}
		else if (ft_strncmp(msg, "$JOIN::", proto_msg_end_pos) == 0)
		{
			printf(KGRN "[Server]: JOIN PROTOCOL request received will be treated.\n" KRESET);
			protocol_request_join(serv, client, msg, proto_msg_end_pos + 1);
		}
		else
		{
			printf(KRED "[Server]: protocol format ok, but not a recognized protocol"
				" request.\n" KRESET);
		}
	}
	else
	{
		printf(KMAG "[Server]: Not a protocol msg! - [client #%d sock %d]: [%s]\n" KRESET,
			client->id, client->sock, msg);
		send_msg(client, KRED "[Server]: PROTOCOL ERROR - This is not a protocol input: " KRESET);
		send_msg(client, "[");
		send_msg(client, msg);
		send_msg(client, "]\n---- Closing connection ----\n");
		client->to_be_disconnected = 1;
	}
}

void	protocol_auth_errmsg(t_client *client)
{
	printf(KMAG "[Server]: Client not authentified.\n" KRESET);
	send_msg(client, "$ERRSERVMSG::Authentify first with"
		" PROTOCOL '$NICK::aleung-c' then '$JOIN::#default' \n");
	return ;
}

/*
**	In my protocol, msg between server and client must have this form: [$MSG::XXXX\n]
**	Everything following the :: will be the user input.
*/

int		get_protocol_msg_end_pos(char *msg)
{
	int			i;

	i = 0;
	if (!msg[i] || msg[i] != '$')
	{
		return (-1);
	}
	while (msg[i] && i < PROTOCOL_MAX_MSG_SIZE)
	{
		if (msg[i] && msg[i] == ':' && msg[i + 1] && msg[i + 1] == ':')
			return (i + 1);
		i++;
	}
	return (-1);
}
