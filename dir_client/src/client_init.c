/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:43:55 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/30 18:43:57 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	init_client_vars(t_client *client)
{
	client->hostname = NULL;
	client->is_port_set = 0;
	client->port = -1;
	client->is_running = 1;
	client->is_connected = 0;
	client->to_be_disconnected = 0;
	client->is_authentified = 0;
	client->default_nick_sent = 0;
	client->default_nick_refused = 0;
	client->nick_sent = 0;
	client->nick_refused = 0;
	client->nick_validated = 0;
	client->join_sent = 0;
	client->join_validated = 0;

	client->read_fd_set = (fd_set *)s_malloc((sizeof(fd_set)));
	client->write_fd_set = (fd_set *)s_malloc((sizeof(fd_set)));
	clear_circular_buffer(&client->recv_buffer);
	clear_circular_buffer(&client->write_buffer);
}
