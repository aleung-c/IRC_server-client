/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_input_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:16:30 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/24 18:16:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	For each client, we will check the content of their recv_buffer
**	and check what they have sent.
**	We start by checking if they respect protocol, then we parse their input.
*/

void	process_clients_inputs(t_serveur *serv)
{
	t_client	*client_i;
	char		*msg;

	client_i = serv->client_handler.clients_list;
	while (client_i)
	{
		if ((msg = get_buffer_msg(&client_i->recv_buffer)))
		{
			printf(KMAG "Extracted msg: [%s] len: %d\n" KRESET,
				msg, (int)ft_strlen(msg));
			parse_client_protocol_msg(serv, client_i, msg);
			free(msg);
		}
		else if (client_i->recv_buffer.is_waiting == 1)
		{
			printf(KYEL "[Client #%d sock %d]: sent msg too long"
						" -> cutting msg\n" KRESET,
				client_i->id, client_i->sock);
				client_i->recv_buffer.is_waiting = 0;
			clear_circular_buffer(&client_i->recv_buffer);
		}
		client_i = client_i->next;
	}
}
