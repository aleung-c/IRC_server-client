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
	ft_printfstr(KGRN "\nNew client connected, sock : ", NULL);
	ft_putnbr(client->sock);
	ft_putchar('\n');
}