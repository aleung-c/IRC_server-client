/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_buffer_sending.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:05:58 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/25 18:06:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	High level function: will fill the buffer with size check and stuff 
**	to be sent at the next select loop turn.
*/

void	send_msg(t_client *client, char *msg)
{
	if ((get_buffer_space(&client->write_buffer) - (int)strlen(msg)) >= 0)
	{
		write_into_buffer(&client->write_buffer, msg, strlen(msg));
	}
	else
	{
		printf(KMAG "[Serveur]: Serveur send buffer full\n" KRESET);
	}
}

/*
**	Put the datas from the buffer into the static tmp buffer for sending.
*/
int		extract_datas_to_send(t_circular_buffer *buffer, char *send_buffer)
{
	int		i;
	int		write_pos;

	i = 0;
	while (buffer->len && i < MSG_SIZE)
	{
		write_pos = (buffer->start + i) % BUFFER_SIZE;
		send_buffer[i] = buffer->data[write_pos];
		i++;
		buffer->len--;
	}
	buffer->start = write_pos + 1;
	return (i);
	// DEBUG PRINT
	// char *buff_cpy = ft_strdup(buffer->data);
	// replace_nl(buff_cpy, ft_strlen(buff_cpy));
	// printf("in buff: [%.*s]\n", BUFFER_SIZE, buff_cpy);
}
