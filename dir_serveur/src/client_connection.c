/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:40:00 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/22 17:40:02 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	Called in main loop when the serveur sock receive a modification
**	-> meaning new client is connected, and its socket will be stocked.
*/

void			new_client_connection(t_serveur *serv)
{
	int					c_sock;
	t_client			*client;

	ft_printfstr(KGRN "\n- New client connection process started -\n" KRESET, NULL);
	if ((c_sock = accept_connection(serv)) < 0)
		return ;
	serv->sock_endpoint = c_sock > serv->sock_endpoint ? c_sock :
	serv->sock_endpoint;
	ft_printfstr("sock_endpoint: ", NULL);
	ft_putnbr(serv->sock_endpoint);
	client = create_new_client(serv, c_sock);
	ft_printfstr(KGRN "\nNew client connected, sock: %d\n" KRESET, &(client->sock));
	new_client_auth_request(client);
}

void		new_client_auth_request(t_client *client)
{
	send_msg(client, "$SERVMSG::--- Connected to aleung-c's IRC SERVER ---\n");
	send_msg(client, "$SERVMSG::\n");
	send_msg(client, "$SERVMSG::----- Please authenticate with:\n");
	send_msg(client, "$SERVMSG::----- $NICK::aleung-c\n");
	send_msg(client, "$SERVMSG::----- $JOIN::#default\n\n");
}

void		new_client_auth_welcome(t_client *client)
{
	send_msg(client, "$SERVMSG::    _   _    ___ _   _ _  _  ___      ___  \n");
	send_msg(client, "$SERVMSG::   /_\\ | |  | __| | | | \\| |/ __|___ / __| \n");
	send_msg(client, "$SERVMSG::  / _ \\| |__| _|| |_| | .` | (_ |___| (__  \n");
	send_msg(client, "$SERVMSG:: /_/_\\_\\____|___|\\___/|_|\\_|\\___|____\\___| \n");
	send_msg(client, "$SERVMSG:: |_ _| _ \\/ __| / __| __| _ \\ \\ / / __| _ \\\n");
	send_msg(client, "$SERVMSG::  | ||   / (__  \\__ \\ _||   /\\ V /| _||   /\n");
	send_msg(client, "$SERVMSG:: |___|_|_\\___| |___/___|_|_\\ \\_/ |___|_|_\\\n");
	send_msg(client, "$SERVMSG::                                           \n");
	send_msg(client, "$SERVMSG::###################################\n");
	send_msg(client, "$SERVMSG:: Welcome to aleung-c's irc server!\n");
	send_msg(client, "$SERVMSG::###################################\n\n");
	send_msg(client, "$SERVMSG::Command list:\n");
	send_msg(client, "$SERVMSG::/nick <nickname> : change your default nick.\n");
	send_msg(client, "$SERVMSG::/join <#chan> : join a channel.\n");
	send_msg(client, "$SERVMSG::/leave <#chan> : leave a channel.\n");
	send_msg(client, "$SERVMSG::/list : display list of server's channels.\n");
	send_msg(client, "$SERVMSG::/who : get list of connected users on your channels.\n");
	send_msg(client, "$SERVMSG::/amsg <message> : send a message to all joined channels.\n");
	send_msg(client, "$SERVMSG::/msg <nick> <message> : send a message to a user.\n");
	send_msg(client, "$SERVMSG::/quit or /exit : Leave the server and closes the connection.\n\n");
}

/*
**	Small function to accept the connection detected on the
**	serveur's sock. Protected in case of error.
*/

int				accept_connection(t_serveur *serv)
{
	int						c_sock;
	struct sockaddr_in		c_sin;
	socklen_t				c_sin_size;

	c_sin_size = sizeof(c_sin);
	if ((c_sock = accept(serv->serveur_sock,
		(struct sockaddr *)&c_sin, &c_sin_size)) < 0)
	{
		ft_printfstr(KRED "accept() error.\n" KRESET, NULL);
	}
	return (c_sock);
}

/*
**	TODO: most leaks here.
*/

void	client_disconnect(t_serveur *serv, t_client *client)
{
	printf(KYEL "[Serveur]:%s client #%d (sock %d) disconnected.\n",
		KRESET, client->id, client->sock);
	close(client->sock);
	clear_client_variables(client);
	remove_client_from_list(serv, client);
}

void	clear_client_variables(t_client *client)
{
	t_channel_list	*tmp;
	t_channel_list	*to_free;

	if (client->channels_joined)
	{
		tmp = client->channels_joined;
		while (tmp)
		{
			remove_client_from_chan(tmp->chan_ptr, client);
			to_free = tmp;
			tmp = tmp->next;
			free(to_free);
		}
	}
}
