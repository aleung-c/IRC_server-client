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

void	cmd_join(t_serveur *serv, t_client *client, char *msg, int user_msg_start)
{
	char		**lexed_msg;
	t_channel	*channel;

	(void)serv;
	lexed_msg = string_lexer(msg + user_msg_start, ' ');
	if (get_array_count(lexed_msg) > 2)
	{
		printf("[Server]: Too many arguments for join command: [%s]\n",
			msg + user_msg_start);
		send_msg(client, "$SERVMSG::Too many arguments for command /join\n");
		return ;
	}
	if (ft_strlen(lexed_msg[1]) > MAX_CHANNEL_NAME_LEN)
	{
		printf("[Server]: Channel name too long(%d char max): [%s]\n",
			MAX_CHANNEL_NAME_LEN, msg + user_msg_start);
		send_msg(client, "$SERVMSG::Channel name too long for command /join\n");
		return ;
	}
	if ((channel = get_channel(serv, lexed_msg[1])))
	{
		// create channel.
		//channel = create_new_chan(serv, lexed_msg[1]);
	}
	// join the channel
	//add_chan_to_client.
	ft_memcpy(client->nickname, lexed_msg[1], MAX_NICK_LEN);
	send_msg(client, "$SERVMSG:: Nickname changed to: [");
	send_msg(client, lexed_msg[1]);
	send_msg(client, "]\n");
}
