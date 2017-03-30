/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:39:23 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:39:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	print_reception(char *msg)
{
	int i;

	i = 0;
	printf(KCYN "<<<<< [client]:%s\n", KRESET);
	write(1, "\t[", 2);
	while (msg[i] && msg[i] != MSG_DELIM)
	{
		i++;
	}
	write(1, msg, i);
	if (msg[i] == '\n')
		write(1, "*]\n", 3);
	else
		write(1, "]\n", 2);
	return ;
}

void	*s_malloc(size_t size)
{
	void	*ret;

	if (!(ret = malloc(size)))
		exit(-1);
	return (ret);
}

void	print_sending(char *msg, int len)
{
	char	*msg_cpy;

	msg_cpy = ft_strdup(msg);
	replace_nl(msg_cpy, ft_strlen(msg_cpy));
	printf(KYEL ">>>>> [client]: %s [%.*s]\n",
		KRESET, len, msg_cpy);
	free(msg_cpy);
}

void	replace_nl(char *str, int len)
{
	str[len] = '\0';
	while (len > 0)
	{
		if (str[len] == '\n')
		{
			str[len] = '*';
		}
		len--;
	}
}

/*
**	Get length until first delimiter c. Does not check boundaries!!
**	Best used after most size checks.
*/

int		get_len_to_delim(char *msg, char c)
{
	int i;

	i = 0;
	while (msg[i] && msg[i] != c)
	{
		if (msg[i] == c)
			return (i);
		i++;
	}
	return (i);
}
