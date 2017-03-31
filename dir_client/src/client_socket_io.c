/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_socket_io.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:12:26 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/30 19:12:27 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	check_socket_io(t_client *client)
{
	int			read_ret;

	if (FD_ISSET(client->sock, client->read_fd_set))
	{
		// client sent datas to be recv()ed.
		// but, if datas received == 0, it means client disconected.
		read_ret = read_socket(client);
		if (read_ret == 0)
		{
			close_connection(client);
		}
		// -> all good, datas collected in circ buffs.
	}
	if (client && FD_ISSET(client->sock, client->write_fd_set))
	{
		// client may send datas to client.
		write_socket(client);
	}
	// no msg waiting to be sent, disconnect him.
	if (client->write_buffer.len == 0
		&& client->to_be_disconnected == 1)
		close_connection(client);
}

int		read_socket(t_client *client)
{
	static char		recv_buffer[MSG_SIZE + 1];
	int				ret;
	int				buff_free_space;

	buff_free_space = get_buffer_space(&client->recv_buffer);
	if (buff_free_space > 0)
	{
		ret = recv(client->sock, recv_buffer, buff_free_space, 0);
		recv_buffer[ret] = '\0';
		write_into_buffer(&client->recv_buffer, recv_buffer, ft_strlen(recv_buffer));
		//print_reception(recv_buffer, client);
		if (ft_strlen(recv_buffer) != 0)
			printf("receiveid: [%s]\n", recv_buffer);
		return (ret);
	}
	else if (client->recv_buffer.is_waiting == 0)
	{
		printf(KYEL "[Client]: Buffer full ...\n" KRESET);
		client->recv_buffer.is_waiting = 1;
	}
	return (-1);
}

void	write_socket(t_client *client)
{
	static char		send_buffer[MSG_SIZE + 1];
	int				to_send;
	int				ret;

	if (client->write_buffer.len > 0)
	{
		// there are datas to be sent.
		to_send = extract_datas_to_send(&client->write_buffer, send_buffer);
		ret = send(client->sock, send_buffer, to_send, 0);
		print_sending(send_buffer, to_send);
		if (ret == -1)
		{
			printf(KRED "send() error.\n" KRESET);
			exit (-1);
		}
	}
}