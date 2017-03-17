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

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

/*
**	Libft's functions.
*/

int		ft_atoi(const char *str)
{
	int i;
	int neg;
	int num;
	int chiffre;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	neg = 1;
	chiffre = 0;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i - 1] == '-')
		neg = -1;
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		chiffre = str[i] - 48;
		num = (num * 10) + chiffre;
		i++;
	}
	return (num * neg);
}

int		ft_isdigit(int c)
{
	if ((c < '0') || (c > '9'))
		return (0);
	else
		return (1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(48 + n);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	*s_malloc(size_t size)
{
	void	*ret;

	if (!(ret = malloc(size)))
		exit(-1);
	return (ret);
}