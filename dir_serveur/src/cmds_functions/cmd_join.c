/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:48:53 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/27 17:48:54 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/serveur.h"

void		cmd_join(t_serveur *serv, t_client *client, char *msg,
					int user_msg_start)
{
	char		**lexed_msg;
	t_channel	*channel;

	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if ((cmd_join_parse_args(lexed_msg, client, msg, user_msg_start)) == -1)
		return (free_lexed_array(lexed_msg));
	if (!(channel = get_chan_from_list(serv->channel_list, lexed_msg[1])))
		channel = create_new_chan(serv, lexed_msg[1]);
	else if (get_chan_from_list(client->channels_joined, lexed_msg[1]))
	{
		printf(KMAG "[Server]: Client already in that channel,"
				"now current.\n" KRESET);
		send_msg(client, "$SERVMSG::Already joined channel.\n");
		send_msg(client, "$SERVMSG::Changed current channel to [");
		send_msg(client, lexed_msg[1]);
		send_msg(client, "]\n$PROMPT::\n");
		client->current_channel = channel;
		free_lexed_array(lexed_msg);
		return ;
	}
	else
		printf(KGRN "[Server]: Client joined existing channel!\n" KRESET);
	client_joins_chan(client, channel);
	free_lexed_array(lexed_msg);
}

int			cmd_join_parse_args(char **lexed_msg, t_client *client,
								char *msg, int user_msg_start)
{
	int		error;

	error = 0;
	if (!lexed_msg || get_array_count(lexed_msg) != 2)
	{
		printf("[Server]: Invalid arguments for join command: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Invalid arguments for"
						" /join\n$PROMPT::\n");
		return (-1);
	}
	else if (lexed_msg[1] && ft_strlen(lexed_msg[1]) > MAX_CHANNEL_NAME_LEN)
	{
		printf("[Server]: Channel name too long(%d char max): [%.*s...]\n",
			MAX_CHANNEL_NAME_LEN, MAX_CHANNEL_NAME_LEN / 2,
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Channel name too"
						" long for /join\n$PROMPT::\n");
		return (-1);
	}
	return (cmd_join_parse_args_part2(lexed_msg, client, msg, user_msg_start));
}

int			cmd_join_parse_args_part2(char **lexed_msg,
					t_client *client, char *msg, int user_msg_start)
{
	if (lexed_msg[1][0] && lexed_msg[1][0] != '#')
	{
		printf("[Server]: Channel name must start with '#': [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Channel name must"
						" start with '#'\n$PROMPT::\n");
		return (-1);
	}
	else if (ft_strlen(lexed_msg[1]) == 1)
	{
		printf("[Server]: Channel must contain letters: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$ERRSERVMSG::Channel name must"
						" contain letters\n$PROMPT::\n");
		return (-1);
	}
	else if (chan_has_forbidden_chars(lexed_msg[1]) == 1)
	{
		send_msg(client, "$ERRSERVMSG::Channel name invalid\n$PROMPT::\n");
		return (-1);
	}
	return (0);
}
