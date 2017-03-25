/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:14:30 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/24 16:14:32 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	Write into the circular buffer. May be used for reading and for sending.
**	Warning: does not check for end of buffer! You may erase current
**	datas with this.
*/

void	write_into_buffer(t_circular_buffer *buffer, char *str, int len)
{
	int i;
	int write_pos;

	i = 0;
	while (len && str[i])
	{
		write_pos = (buffer->start + buffer->len + i) % BUFFER_SIZE;
		buffer->data[write_pos] = str[i];
		i++;
		len--;
	}
	buffer->len += i;
	buffer->end = write_pos;

	// DEBUG PRINT
	char *buff_cpy = ft_strdup(buffer->data);
	replace_nl(buff_cpy, ft_strlen(buff_cpy));
	printf("in buff: [%.*s]\n", BUFFER_SIZE, buff_cpy);
}

/*
**	To know the amount of space left in the circ buff.
*/

int		get_buffer_space(t_circular_buffer *buffer)
{
	int ret;

	ret = BUFFER_SIZE - buffer->len;
	if (ret > MSG_SIZE)
		ret = MSG_SIZE;
	return (ret);
}

void	clear_circular_buffer(t_circular_buffer *buffer)
{
	ft_memset(buffer->data, 0, BUFFER_SIZE);
	buffer->is_waiting = 0;
	buffer->start = 0;
	buffer->end = 0;
	buffer->len = 0;
}

/*
**	This function takes the current string from the buffer.
**	Does not modify the buffer. Useful for read only operations.
*/

char	*get_buffer_str(t_circular_buffer *buffer)
{
	char	*str;
	int 	i;

	i = 0;
	str = (char *)s_malloc(buffer->len * sizeof(char) + 1);
	str[buffer->len] = '\0';
	while (i != buffer->len)		
	{
		str[i] = buffer->data[(buffer->start + i) % BUFFER_SIZE];
		i++;
	}
	return (str);
}
