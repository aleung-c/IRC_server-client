/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connection_msg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 16:49:19 by aleung-c          #+#    #+#             */
/*   Updated: 2017/04/05 16:49:20 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

void		new_client_auth_request(t_client *client)
{
	send_msg(client, "$SERVMSG::--- Connected to aleung-c's IRC SERVER ---\n");
	send_msg(client, "$SERVMSG::\n");
	send_msg(client, "$SERVMSG::----- Please authenticate with:\n");
	send_msg(client, "$SERVMSG::----- $NICK::aleung-c\n");
	send_msg(client, "$PROTOREQ::ASK::NICK::----- $NICK::aleung-c\n");
	send_msg(client, "$SERVMSG::----- $JOIN::#default\n\n");
}

void		new_client_auth_welcome(t_client *client)
{
	send_msg(client, "$SERVMSG::    _   _    ___ _   _ _  _  ___      "
						"___  \n");
	send_msg(client, "$SERVMSG::   /_\\ | |  | __| | | | \\| |/ __|___"
						" / __| \n");
	send_msg(client, "$SERVMSG::  / _ \\| |__| _|| |_| | .` | (_ |___| "
						"(__  \n");
	send_msg(client, "$SERVMSG:: /_/_\\_\\____|___|\\___/|_|\\_|\\___|"
						"____\\___| \n");
	send_msg(client, "$SERVMSG:: |_ _| _ \\/ __| / __| __| _ \\ \\ / / __"
						"| _ \\\n");
	send_msg(client, "$SERVMSG::  | ||   / (__  \\__ \\ _||   /\\ V /| _|"
						"|   /\n");
	send_msg(client, "$SERVMSG:: |___|_|_\\___| |___/___|_|_\\ \\_/ |___|"
						"_|_\\\n");
	send_msg(client, "$SERVMSG::                                         "
						"  \n");
	send_msg(client, "$SERVMSG::###################################\n");
	send_msg(client, "$SERVMSG:: Welcome to aleung-c's irc server!\n");
	send_msg(client, "$SERVMSG::###################################\n\n");
	new_client_auth_welcome_2(client);
}

void		new_client_auth_welcome_2(t_client *client)
{
	send_msg(client, "$SERVMSG::Command list:\n");
	send_msg(client, "$SERVMSG::/nick <nickname> : change your default"
						" nick.\n");
	send_msg(client, "$SERVMSG::/join <#chan> : join a channel.\n");
	send_msg(client, "$SERVMSG::/leave <#chan> : leave a channel.\n");
	send_msg(client, "$SERVMSG::/list : display list of server's channels.\n");
	send_msg(client, "$SERVMSG::/who : get list of connected users on"
						" your channels.\n");
	send_msg(client, "$SERVMSG::/amsg <message> : send a message to all"
						" joined channels.\n");
	send_msg(client, "$SERVMSG::/msg <nick> <message> : send a message"
						" to a user.\n");
	send_msg(client, "$SERVMSG::/quit or /exit : Leave the server and"
						" closes the connection.\n\n");
	send_msg(client, "$SERVMSG::You are in channel ");
	send_msg(client, client->current_channel->name);
	send_msg(client, "\n$PROMPT::\n");
}
