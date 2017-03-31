/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:53:48 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/30 18:53:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	client_main_loop(t_client *client)
{
	struct timeval		t;

	while (client->is_running == 1)
	{
		init_fd(client);
		if (select(client->sock + 1, client->read_fd_set,
				client->write_fd_set, NULL, set_select_timeout(&t)) < 0)
		{
			printf(KRED "Select() Error.\n" KRESET);
			perror("select");
			exit(-1);
		}
		check_fd_sets(client);
	}
}

void	init_fd(t_client *client)
{
	FD_ZERO(client->read_fd_set);
	FD_ZERO(client->write_fd_set);
	FD_SET(STDIN_FILENO, client->read_fd_set);
	if (client->is_connected)
	{
		FD_SET(client->sock, client->read_fd_set);
		FD_SET(client->sock, client->write_fd_set);
	}
}

struct timeval		*set_select_timeout(struct timeval *t)
{
	t->tv_sec = 0;
	t->tv_usec = 100;
	return (t);
}

void				check_fd_sets(t_client *client)
{
	if (FD_ISSET(STDIN_FILENO, client->read_fd_set))
	{
		read_user_input(client);
	}
	check_socket_io(client);
	process_receiveid_msg(client);
	return ;
}
