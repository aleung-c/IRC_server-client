/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_buffer_extraction.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 15:10:06 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/25 15:10:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"



/*
**	This function extracts the current string from the buffer.
**	It does modify the buffer, and take everything up to
**	the len of the buffer.
*/

char	*extract_buffer_str(t_circular_buffer *buffer)
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
	buffer->len = 0;
	buffer->start = (buffer->start + i) % BUFFER_SIZE;
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
	buffer->start = (buffer->start + i + 1) % BUFFER_SIZE;
	buffer->len -= i + 1;
	return (str);
}

/*
**	Search the buffer for the delimiter char.
**	If it is found, return its position from start.
**	Otherwise, returns 0.
*/

int		search_buffer_delim(t_circular_buffer *buffer)
{
	int i;

	i = 0;
	while (i != buffer->len)		
	{
		if (buffer->data[(buffer->start + i) % BUFFER_SIZE] == MSG_DELIM)
		{
			if (i == 0)
			{
				buffer->start = (buffer->start + 1) % BUFFER_SIZE;
				if (buffer->len > 0)
					buffer->len--;
			}
			return (i);
		}
		i++;
	}
	return (0);
}

/*
**	For a given buffer, will check if the message delimiter is present.
**	If yes, we will extract this message and make the buffer advance.
**	If not, return NULL;
*/

char	*get_buffer_msg(t_circular_buffer *buffer)
{
	char	*msg;
	int		i;

	if ((i = search_buffer_delim(buffer)) != 0)
	{
		msg = get_buffer_delimstr(buffer, i);
		return (msg);
	}
	else
	{
		return (NULL);
	}
}
