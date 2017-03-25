/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_init_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:42:11 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/25 18:42:12 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	we initialize the list of command the client can send.
*/

void	init_cmd_list(t_serveur *serv)
{
	serv->chat_cmd_table = s_malloc(sizeof(t_chat_cmd) * NB_OF_CMDS);
	serv->chat_cmd_table[0].name = "/nick";
	serv->chat_cmd_table[0].function = NULL;
	serv->chat_cmd_table[1].name = "/join";
	serv->chat_cmd_table[1].function = NULL;
	serv->chat_cmd_table[2].name = "/leave";
	serv->chat_cmd_table[2].function = NULL;
	serv->chat_cmd_table[3].name = "/who";
	serv->chat_cmd_table[3].function = NULL;
	serv->chat_cmd_table[4].name = "/msg";
	serv->chat_cmd_table[4].function = NULL;
}
