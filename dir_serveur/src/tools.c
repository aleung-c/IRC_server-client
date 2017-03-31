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

#include "../includes/serveur.h"

/*
** A very simple version of format printing taking only one char *.
*/

void	ft_printfstr(char *format, void *arg)
{
	int i;

	i = 0;
	while (arg && format[i])
	{
		if (arg && format[i] == '%' && format[i + 1])
		{
			write (1, format, i);
			if (format[i + 1] == 's')
			{
				write(1, (char *)arg, ft_strlen(arg));
			}
			else if (format[i + 1] == 'd')
			{
				ft_putnbr(*(int *)arg);
			}
			write(1, format + i + 2, ft_strlen(format) - i - 2);
			return ;
		}
		i++;
	}
	write(1, format, ft_strlen(format));
}

void	*s_malloc(size_t size)
{
	void	*ret;

	if (!(ret = malloc(size)))
		exit(-1);
	return (ret);
}

void	print_reception(char *msg, t_client *client)
{
	int i;

	i = 0;
	printf(KCYN "<<<<< [client #%d, sock %d]:%s\n",
		client->id, client->sock, KRESET);
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

void	print_sending(char *msg, t_client *client, int len)
{
	char	*msg_cpy;

	msg_cpy = ft_strdup(msg);
	replace_nl(msg_cpy, ft_strlen(msg_cpy));
	printf(KYEL ">>>>> [client #%d, sock %d]: %s [%.*s]\n",
		client->id, client->sock, KRESET, len, msg_cpy);
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
