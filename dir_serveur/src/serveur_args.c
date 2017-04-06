/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:57:43 by aleung-c          #+#    #+#             */
/*   Updated: 2017/04/06 14:57:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

int		get_args(t_serveur *serv, int argc, char **argv)
{
	if (argc == 2)
	{
		if (check_port_format(argv[1]) != -1)
		{
			serv->port = ft_atoi(argv[1]);
			if (serv->port < 1024 || serv->port > 65535)
			{
				printf(KRED "Bad port: 1024 <> 65535\n" KRESET);
				return (-1);
			}
		}
		else
		{
			printf(KRED "Invalid port format\n" KRESET);
			return (-1);
		}
	}
	else
	{
		print_usage(argv[0]);
		return (-1);
	}
	return (0);
}

int		check_port_format(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) != 1)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

void	print_usage(char *arg)
{
	ft_printfstr(KRED "Usage: %s <port>\n" KRESET, arg);
}
