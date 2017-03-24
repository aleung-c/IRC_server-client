/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_main_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:35:55 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 17:35:56 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	Main loop of the server: init fd, select, read datas...
*/

void				serveur_main_loop(t_serveur *serv)
{
	int					ret_select;
	struct timeval		t;

	ft_printfstr( KCYN "- Server Awaiting data -\n" KRESET, NULL);
	while (serv->is_running == 1)
	{
		init_fd(serv);
		ret_select = select(serv->sock_endpoint + 1, serv->read_fd_set,
			serv->write_fd_set, NULL, set_select_timeout(&t));
		if (ret_select < 0)
		{
			ft_printfstr(KRED "[Serveur]: Select() error.\n" KRESET, NULL);
			perror("select() errno");
			exit (-1);
		}
		check_fd_sets(serv);
	}
	return ;
}

void				init_fd(t_serveur *serv)
{
	t_client	*client_i;

	FD_ZERO(serv->read_fd_set);
	FD_ZERO(serv->write_fd_set);
	FD_SET(STDIN_FILENO, serv->read_fd_set);
	FD_SET(serv->serveur_sock, serv->read_fd_set);
	client_i = serv->client_handler.clients_list;
	while (client_i)
	{
		FD_SET(client_i->sock, serv->read_fd_set);
		FD_SET(client_i->sock, serv->write_fd_set);
		client_i = client_i->next;
	}
}

struct timeval		*set_select_timeout(struct timeval *t)
{
	t->tv_sec = 0;
	t->tv_usec = 100;
	return (t);
}

void				check_fd_sets(t_serveur *serv)
{
	if (FD_ISSET(STDIN_FILENO, serv->read_fd_set))
	{
		ft_printfstr(KGRN "[Serveur]: Closing server." KRESET, NULL);
		exit(0);
	}
	// modif sur la sock du serveur.
	if (FD_ISSET(serv->serveur_sock, serv->read_fd_set))
	{
		new_client_connection(serv);
	}
	check_sockets_io(serv);
	process_clients_inputs(serv);
	
	return ;
}
