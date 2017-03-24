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
	char	*msg_cpy;

	msg_cpy = ft_strdup(msg);
	replace_nl(msg_cpy, ft_strlen(msg_cpy));
	printf(KCYN "<<<< [client #%d, s #%d]: " KRESET,
		client->id, client->sock);
	printf("[%s]\n", msg_cpy);
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