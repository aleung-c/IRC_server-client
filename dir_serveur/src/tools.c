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

void	ft_printfstr(char *format, char *msg)
{
	int i;

	i = 0;
	while (format[i])
	{
		if (msg && format[i] == '%' && format[i + 1]
			&& format[i +1] == 's')
		{
			write (1, format, i);
			write(1, msg, ft_strlen(msg));
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