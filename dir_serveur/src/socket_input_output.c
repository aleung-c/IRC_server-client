/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_input_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:00:47 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/24 14:00:48 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	In here, we will check the data input reception and output sending
**	for each connected socket.
**	FD_ISSET will tell us if the client CAN or not recv() and send();
*/

void	check_sockets_io(t_serveur *serv)
{
	t_client	*client_i;
	int			read_ret;

	client_i = serv->client_handler.clients_list;
	while (client_i)
	{
		if (FD_ISSET(client_i->sock, serv->read_fd_set))
		{
			read_ret = read_client_socket(serv, client_i);
			if (read_ret == 0)
			{
				client_disconnect(serv, client_i);
			}
		}
		if (client_i && FD_ISSET(client_i->sock, serv->write_fd_set))
		{
			write_client_socket(serv, client_i);
		}
		if (client_i->write_buffer.len == 0
			&& client_i->to_be_disconnected == 1)
			client_disconnect(serv, client_i);
		if (client_i)
			client_i = client_i->next;
	}
}

/*
**	This function will read into the temp static buffer with recv.
**	Everything from this buffer will be put into the
**	personal circular buffer of the client.
*/

int		read_client_socket(t_serveur *serv, t_client *client)
{
	static char		recv_buffer[MSG_SIZE + 1];
	int				ret;
	int				buff_free_space;

	(void)serv;
	buff_free_space = get_buffer_space(&client->recv_buffer);
	if (buff_free_space > 0)
	{
		ret = recv(client->sock, recv_buffer, buff_free_space, 0);
		recv_buffer[ret] = '\0';
		write_into_buffer(&client->recv_buffer, recv_buffer,
			ft_strlen(recv_buffer));
		print_reception(recv_buffer, client);
		return (ret);
	}
	else if (client->recv_buffer.is_waiting == 0)
	{
		printf(KYEL "[Client #%d sock %d]:"
					" Buffer waiting for processing...\n" KRESET,
					client->id, client->sock);
		client->recv_buffer.is_waiting = 1;
		client->recv_buffer.data[client->recv_buffer.end] = '\n';
	}
	return (-1);
}

/*
**	This function will send the datas on the write buffer to
**	the client's socket, if there are any to send.
*/

void	write_client_socket(t_serveur *serv, t_client *client)
{
	static char		send_buffer[MSG_SIZE + 1];
	int				to_send;
	int				ret;

	(void)serv;
	if (client->write_buffer.len > 0)
	{
		to_send = extract_datas_to_send(&client->write_buffer, send_buffer);
		ret = send(client->sock, send_buffer, to_send, 0);
		print_sending(send_buffer, client, to_send);
		if (ret == -1)
		{
			printf(KRED "send() error%s\n", KRESET);
			exit(-1);
		}
	}
}
