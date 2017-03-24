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

void	write_into_buffer(t_circular_buffer *buffer, char *received, int len)
{
	int i;
	int write_pos;

	i = 0;
	while (len && received[i])
	{
		write_pos = (buffer->start + buffer->len + i) % BUFFER_SIZE;
		buffer->data[write_pos] = received[i];
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

/*
**	Extract the string from the buffer until the delimiter.
**	Moves the buffer start and len.
*/

char	*get_buffer_delimstr(t_circular_buffer *buffer, int delim_count)
{
	char	*str;
	int 	i;

	i = 0;
	str = (char *)s_malloc(delim_count * sizeof(char) + 1);
	str[delim_count] = '\0';
	while (i < delim_count)		
	{
		str[i] = buffer->data[(buffer->start + i) % BUFFER_SIZE];
		i++;
	}
	buffer->start = (buffer->start + i) % BUFFER_SIZE;
	buffer->len -= i;
	return (str);
}

int		search_buffer_delim(t_circular_buffer *buffer)
{
	int i;

	i = 0;
	while (i != buffer->len)		
	{
		if (buffer->data[(buffer->start + i) % BUFFER_SIZE] == MSG_DELIM)
			return (i);
		i++;
	}
	return (0);
}

/*
**	For a given buffer, will check if the message delimiter is present.
**	If yes, we will extract this message and make the buffer advance.
**	If not, return NULL;
*/

char	*get_buffer_cmd(t_circular_buffer *buffer)
{
	char	*cmd;
	int		i;

	if ((i = search_buffer_delim(buffer)))
	{
		cmd = get_buffer_delimstr(buffer, i);
		return (cmd);
	}
	else
	{
		return (NULL);
	}
}
