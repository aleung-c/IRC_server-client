/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_request_join.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:00:48 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 14:00:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

void	protocol_request_join(t_serveur *serv, t_client *client, char *msg,
								int proto_msg_delim_pos)
{
	char		**lexed_msg;
	t_channel	*channel;

	lexed_msg = string_lexer(msg + proto_msg_delim_pos, ' ');
	if ((protocol_join_request_parsing(lexed_msg, client, msg,
			proto_msg_delim_pos)) == -1)
		return ;
	if (!(channel = get_chan_from_list(serv->channel_list, lexed_msg[0])))
		channel = create_new_chan(serv, lexed_msg[0]);
	else if (get_chan_from_list(client->channels_joined, lexed_msg[0]))
	{
		printf(KMAG "[Server]: Client already in that channel,"
				"now current.\n" KRESET);
		send_msg(client, "$SERVMSG::Already joined channel.\n");
		send_msg(client, "$SERVMSG::Changed current channel to [");
		send_msg(client, lexed_msg[0]);
		send_msg(client, "]\n");
		client->current_channel = channel;
		return ;
	}
	else
		printf(KGRN "[Server]: Client joined existing channel!\n" KRESET);
	add_client_to_chan(channel, client);
	add_chan_to_list(&client->channels_joined, channel);
	client->current_channel = channel;
	client->nb_chan_joined += 1;
	send_msg(client, "$SERVMSG::Joined channel [");
	send_msg(client, lexed_msg[0]);
	send_msg(client, "]\n");
	if (client->is_authentified == 0)
	{
		client->is_authentified = 1;
		new_client_auth_welcome(client);
	}
	free_lexed_array(lexed_msg);
}

int		protocol_join_request_parsing(char **lexed_msg, t_client *client,
								char *msg, int proto_msg_delim_pos)
{
	int		error;

	error = 0;
	if (!lexed_msg || get_array_count(lexed_msg) > 1)
	{
		printf("[Server]: Invalid arguments for JOIN request: [%s]\n",
			msg + proto_msg_delim_pos);
		send_msg(client, "$ERRSERVMSG::Invalid format for JOIN request protocol.\n");
		error = -1;
	}
	else if (lexed_msg[0] && ft_strlen(lexed_msg[0]) > MAX_CHANNEL_NAME_LEN)
	{
		printf("[Server]: Channel name too long(%d char max): [%s]\n",
			MAX_CHANNEL_NAME_LEN, msg + proto_msg_delim_pos);
		send_msg(client, "$ERRSERVMSG::Channel name too long for"
						" JOIN request protocol.\n");
		error = -1;
	}
	else if (lexed_msg[0][0] && lexed_msg[0][0] != '#')
	{
		printf("[Server]: Channel name must start: [%s]\n",
			msg + proto_msg_delim_pos);
		send_msg(client, "$ERRSERVMSG::Channel name must start with '#'\n");
		error = -1;
	}
	if (lexed_msg && error == -1)
		free_lexed_array(lexed_msg);
	return (error);
}
