/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arg_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 20:42:07 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 20:50:59 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

int		input_args_handling(t_client *client, int argc, char **argv)
{
	if (argc > 3 || argc == 2)
	{
		return (-1);
	}
	else if (argc == 3)
	{
		if (get_hostname(client, argv[1]) == -1)
			return (-1);
		if (get_port(client, argv[2]) == -1)
			return (-1);
		return (0);
	}
	return (0);
}

void	print_usage(char *arg)
{
	if (arg)
		printf(KCYN "Usage: %s [machine [port]]\n" KRESET, arg);
}

/*
**	In here, I'll check the format AND parse the hostname.
*/

int		get_hostname(t_client *client, char *arg)
{
	int i;

	i = 0;
	if (ft_strlen(arg) > HOSTNAME_MAX_LEN)
		printf(KRED "Hostname too long.\n" KRESET);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '.')
		{
			printf(KRED "Bad character in hostname: [%c]\n"
				KRESET, arg[i]);
			return (-1);
		}
		i++;
	}
	client->hostname = arg;
	printf("hostname: %s\n", client->hostname);
	return (0);
}

int		get_port(t_client *client, char *arg)
{
	int		port_ret;

	if (arg[ft_strlen(arg) - 1] == '\n')
		arg[ft_strlen(arg) - 1] = '\0';
	if (check_port_format(arg) != -1)
	{
		port_ret = ft_atoi(arg);
		printf("port caught = %d\n", port_ret);
		if (port_ret < 1024 || port_ret > 65535)
		{
			printf(KRED "Bad port: 1024 <> 65535\n" KRESET);
			return (-1);
		}
		client->port = port_ret;
		client->is_port_set = 1;
	}
	else
	{
		printf(KRED "Invalid port format\n" KRESET);
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
