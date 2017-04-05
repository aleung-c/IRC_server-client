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

void		new_client_connection(t_serveur *serv)
{
	int					c_sock;
	t_client			*client;

	printf(KGRN "\n- New client connection process started -%s\n",
		KRESET);
	if ((c_sock = accept_connection(serv)) < 0)
		return ;
	serv->sock_endpoint = c_sock > serv->sock_endpoint ? c_sock :
	serv->sock_endpoint;
	ft_printfstr("sock_endpoint: ", NULL);
	ft_putnbr(serv->sock_endpoint);
	client = create_new_client(serv, c_sock);
	ft_printfstr(KGRN "\nNew client connected, sock: %d\n" KRESET,
		&(client->sock));
	new_client_auth_request(client);
}

/*
**	Small function to accept the connection detected on the
**	serveur's sock. Protected in case of error.
*/

int			accept_connection(t_serveur *serv)
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

void		client_disconnect(t_serveur *serv, t_client *client)
{
	printf(KYEL "[Serveur]:%s client #%d (sock %d) disconnected.\n",
		KRESET, client->id, client->sock);
	close(client->sock);
	clear_client_variables(client);
	remove_client_from_list(serv, client);
}

void		clear_client_variables(t_client *client)
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
