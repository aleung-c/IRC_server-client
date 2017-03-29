/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:26:46 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:28:14 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

int		main(int argc, char **argv)
{
	t_client	client;

	printf("Hello client\n");
	client.is_port_set = 0;
	if (input_args_handling(&client, argc, argv) != 0)
	{
		print_usage(argv[0]);
		return (0);
	}
	//client_main_loop(&client);
	return (0);
}
