/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_received_msg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 20:50:52 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/30 20:50:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	process_receiveid_msg(t_client *client)
{
	char *msg;

	if ((msg = get_buffer_msg(&client->recv_buffer)))
	{
		printf("Extracted %s%d%s chars: [%s%s%s]\n",
			KYEL, (int)ft_strlen(msg), KRESET,
			KYEL, msg, KRESET);
		if (client->is_authentified == 0)
		{
			parse_auth_msg(client, msg);
		}
		else
		{
			printf("todo: will parse received msg !\n");
		}
	}
}

// todo: maybe problem with finishing \n
void	parse_auth_msg(t_client *client, char *msg)
{
	if (client->is_authentified == 0)
	{
		if (ft_strncmp(msg, "$PROTOREQ::ASK::NICK::", 21) == 0
			&& client->default_nick_sent == 0
			&& client->default_nick_refused == 0)
		{
			send_msg(client, "$NICK::");
			send_msg(client, DEFAULT_NICK);
			send_msg(client, "\n");
			client->default_nick_sent = 1;
		}
		else if (ft_strncmp(msg, "$PROTOREQ::NICK::KO::", 20) == 0)
		{
			if (client->default_nick_sent == 1 && client->default_nick_refused == 0)
			{
				printf(KMAG "[Client]: Default nick refused, select another one :%s\n", KRESET);
				write(1, "$>", 2);
				client->default_nick_refused = 1;
				client->nick_refused = 1;
				client->nick_sent = 0;
			}
			else if (client->nick_sent == 1)
			{
				printf(KMAG "[Client]: Selected nick refused, select another one :%s\n", KRESET);
				write(1, "$>", 2);
				client->nick_refused = 0;
				client->nick_sent = 0;
			}
		}
		else if (ft_strncmp(msg, "$PROTOREQ::NICK::OK::", 20) == 0)
		{
			client->nick_validated = 1;
			send_msg(client, "$JOIN::");
			send_msg(client, DEFAULT_CHAN);
			send_msg(client, "\n");
		}
		else if (ft_strncmp(msg, "$PROTOREQ::JOIN::OK::", 20) == 0)
		{
			client->is_authentified = 1;
			printf(KGRN "[Client]: Authentification SUCCESS -%s\n", KRESET);
		}
	}

}
