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
**	and check what they have sent. Soon it will be time to parse!
*/

void	process_clients_inputs(t_serveur *serv)
{
	t_client	*client_i;
	char		*cmd;

	client_i = serv->client_handler.clients_list;
	while (client_i)
	{
		if ((cmd = get_buffer_cmd(&client_i->recv_buffer)))
		{
			// parse cmd
			printf("Extracted cmd: [%s]\n", cmd);
		}
		else if (client_i->recv_buffer.is_waiting == 1)
		{
			printf(KYEL "[Client #%d sock %d]: sent msg too long -> clearing buff\n" KRESET,
				client_i->id, client_i->sock);
				client_i->recv_buffer.is_waiting = 0;
			clear_circular_buffer(&client_i->recv_buffer);
		}
		client_i = client_i->next;
	}
}



