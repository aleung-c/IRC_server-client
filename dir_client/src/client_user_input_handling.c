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

	ret = read(STDIN_FILENO, user_input_buffer, MSG_SIZE);
	user_input_buffer[ret] = '\0';
	//printf("user wrote: [%s]\n", user_input_buffer);
	if (client->is_connected == 0)
	{
		// not connected, read connect cmd;
		parse_user_connection_cmd(client, user_input_buffer);
	}
	else if (client->is_connected == 1
		&& client->is_authentified == 0)
	{
		parse_user_auth_msg(client, user_input_buffer);
	}
	else 
	{
		parse_user_chat_msg(client, user_input_buffer);
	}
}


void	parse_user_connection_cmd(t_client *client, char *user_input_buffer)
{
	char	**lexed_msg;

	lexed_msg = string_lexer(user_input_buffer, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) != 3
		|| lexed_msg[0][0] != '/')
	{
		return (user_input_error(lexed_msg, "format", "/connect"));
	}
	else
	{
		if (get_hostname(client, lexed_msg[1]) == -1)
		{
			return (user_input_error(lexed_msg, "hostname", "/connect"));
		}
		else if (get_port(client, lexed_msg[2]) == -1)
		{
			return (user_input_error(lexed_msg, "port", "/connect"));
		}

		if (connect_client(client) == -1)
		{
			printf(KMAG "[Client]: Connection to server failed,"
						" try again:%s\n", KRESET);
			put_prompt();
		}
		else
		{
			client->is_connected = 1;
		}
		free_lexed_array(lexed_msg);
	}
}

void	user_input_error(char **lexed_msg, char *type, char *cmd)
{
	free_lexed_array(lexed_msg);
	printf(KMAG "[Client]: Invalid %s for %s%s\n", type, cmd, KRESET);
	put_prompt();
}

void	parse_user_auth_msg(t_client *client, char *user_input)
{
	char	**lexed_msg;

	lexed_msg = string_lexer(user_input, ' ');
	if (!lexed_msg || get_array_count(lexed_msg) != 1)
	{
		return (user_input_error(lexed_msg, "format", "nickname"));
	}
	else
	{
		send_msg(client, "$NICK::");
		send_msg(client, user_input);
		send_msg(client, "\n");
		free_lexed_array(lexed_msg);
		client->nick_sent = 1;
	}
}

void	parse_user_chat_msg(t_client *client, char *user_input)
{
	if (ft_strlen(user_input) < MSG_SIZE)
	{
		send_msg(client, "$MSG::");
		send_msg(client, user_input);
		send_msg(client, "\n");
	}
	else
	{
		printf(KMAG "[Client]: Chat message too long.%s\n", KRESET);
	}
}
