/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 20:55:05 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 20:55:07 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

int		connect_client(t_client *client)
{
	if (!client->hostname || client->is_port_set == -1)
	{
		printf(KMAG "no hostname and port to connect.\n" KRESET);
		return (-1);
	}
	if (client->is_connected == 0)
	{
		if (try_client_connection(client) != -1)
		{
			client->is_connected = 1;
			printf(KGRN "[Client]: Connected to server.\n" KRESET);
		}
		else
			return (-1);
	}
	else
		printf("[Client]: Already connected.\n");
	return (0);
}

int		try_client_connection(t_client *client)
{
	struct hostent		*host;
	struct protoent		*proto;

	printf(KCYN "[Client]: - Connecting... -\n" KRESET);
	if ((host = gethostbyname(client->hostname)))
		client->hostname = inet_ntoa(*((struct in_addr **)
			(host->h_addr_list))[0]);
	else
	{
		printf(KRED "[Client]: No such hostname.\n" KRESET);
		return (-1);
	}
	proto = getprotobyname("tcp");
	if (!proto)
	{
		printf(KRED "getprotobyname() error\n" KRESET);
		return (-1);
	}
	return (client_connect_exec(client, proto));
}

int		client_connect_exec(t_client *client, struct protoent *proto)
{
	client->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	client->sin.sin_family = AF_INET;
	client->sin.sin_port = htons(client->port);
	client->sin.sin_addr.s_addr = inet_addr(client->hostname);
	if (connect(client->sock, (const struct sockaddr *)&(client->sin),
		sizeof(client->sin)) == -1)
	{
		printf(KRED "connect() error: cannot connect to hostname\n" KRESET);
		return (-1);
	}
	return (0);
}

void	close_connection(t_client *client)
{
	if (client->is_connected == 1)
	{
		printf(KRED "[Client]: Connection closed."
				" Reconnect with /connect <machine> <port>%s\n",
				KRESET);
		close(client->sock);
		client->is_connected = 0;
		client->is_authentified = 0;
		client->default_nick_sent = 0;
		client->default_nick_refused = 0;
		client->nick_sent = 0;
		client->nick_refused = 0;
		client->nick_validated = 0;
		client->join_sent = 0;
		client->join_validated = 0;
		put_prompt();
	}
}
