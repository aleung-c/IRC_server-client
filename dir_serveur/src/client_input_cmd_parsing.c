/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_input_cmd_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:32:49 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/27 15:32:51 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	First, we want to know the length of found cmd.
**	Then, we compare it to the commands from the dictionnary.
**	The space will be the delimiter of cmds and args.
*/

void	parse_client_chat_cmd(t_serveur *serv, t_client *client, char *msg,
								int msg_start)
{
	int				i;
	size_t			cmd_len;
	t_chat_cmd		*chat_cmd;

	turn_tabs_to_space(msg + msg_start);
	cmd_len = get_len_to_delim(msg + msg_start, ' ');
	if (cmd_len > CMD_MAX_LEN)
	{
		printf("[Server]: chat cmd too long(%d char max): [%s]\n",
			CMD_MAX_LEN, msg + msg_start);
		send_msg(client, "$ERRSERVMSG::Chat command too long.\n$PROMPT::\n");
		return ;
	}
	i = 0;
	chat_cmd = serv->chat_cmd_table;
	while (i < NB_OF_CMDS)
	{
		if (ft_strncmp(msg + msg_start, chat_cmd[i].name,
			ft_strlen(chat_cmd[i].name) - 1) == 0
			&& cmd_len == ft_strlen(chat_cmd[i].name))
		{
			printf(KGRN "[Server]: Found chat command to execute!\n" KRESET);
			chat_cmd[i].function(serv, client, msg, msg_start);
			return ;
		}
		i++;
	}
	printf(KMAG "[Server]: cmd does not exist: [%s]\n" KRESET,
			msg + msg_start);
	send_msg(client, "$ERRSERVMSG::No such chat command.\n$PROMPT::\n");
}
