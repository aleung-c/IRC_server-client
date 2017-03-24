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
			// client sent datas to be recv()ed.
			// but, if datas received == 0, it means client disconected.
			read_ret = read_client_socket(serv, client_i);
			if (read_ret == 0)
			{
				client_disconnect(serv, client_i);
			}
			// -> all good, datas collected in circ buffs.
		}
		if (client_i && FD_ISSET(client_i->sock, serv->write_fd_set))
		{
			// serveur may send datas to client.
			write_client_socket(serv, client_i);
		}
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
		print_reception(recv_buffer, client);
		write_into_buffer(&client->recv_buffer, recv_buffer, ft_strlen(recv_buffer));
		return (ret);
	}
	else if (client->recv_buffer.is_waiting == 0)
	{
		printf(KYEL "[Client #%d sock %d]: Buffer waiting for processing...\n" KRESET,
			client->id, client->sock);
		client->recv_buffer.is_waiting = 1;
	}
	return (-1);
}

/*
**	This function will send the datas on the write buffer to
**	the client's socket, if there are any to send.
*/

void	write_client_socket(t_serveur *serv, t_client *client)
{
	(void)serv;
	(void)client;

}