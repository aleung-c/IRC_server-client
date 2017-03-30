/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_user_input_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:12:16 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/30 19:12:18 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	read_user_input(t_client *client)
{
	static char		user_input_buffer[MSG_SIZE + 1];
	int				ret;

	ret = read(client->sock, user_input_buffer, MSG_SIZE);
	user_input_buffer[ret] = '\0';
	printf("user wrote: [%s]\n", user_input_buffer);
	if (client->is_connected == 0)
	{
		// not connected, read connect cmd;
		parse_user_connection_cmd(client, user_input_buffer);
	}
}


void	parse_user_connection_cmd(t_client *client, char *user_input_buffer)
{
	char	**lexed_msg;

	lexed_msg = string_lexer(user_input_buffer, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) != 3
		|| lexed_msg[0][0] != '/')
	{
		user_connection_error("format");
		return ;
	}
	else
	{
		if (get_hostname(client, lexed_msg[1]) == -1)
		{
			return (user_connection_error("hostname"));
		}
		else if (get_port(client, lexed_msg[2]) == -1)
		{
			return (user_connection_error("port"));
		}

		if (connect_client(client) == -1)
		{
			printf("[Client]: Connection to server failed\n");
			return ;
		}
	}
}

void	user_connection_error(char *type)
{
	printf(KMAG "[Client]: Invalid %s for /connect.%s\n", type, KRESET);

}