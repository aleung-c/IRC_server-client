/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 20:55:05 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 20:55:07 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

int		connect_client(t_client *client)
{
	(void)client;
	// struct hostent		*host;
	
	// if (!isConnected)
	// {
	// 	//cout << KCYN "- Connection attempt... -" KRESET << endl;
	// 	//char * dupHostName = strdup(hostName.c_str());
	// 	if ((host = gethostbyname(hostName.c_str())))
	// 		hostName = inet_ntoa(*((struct in_addr **)(host->h_addr_list))[0]);
	// 	//free(dupHostName);
	// 	proto = getprotobyname("tcp");
	// 	if (!proto)
	// 		throw (CustomException("getprotobyname() error"));
	// 	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	// 	sin.sin_family = AF_INET;
	// 	sin.sin_port = htons(port);
	// 	sin.sin_addr.s_addr = inet_addr(hostName.c_str());
	// 	if (connect(sock, (const struct sockaddr *)&(sin), sizeof(sin)) == -1)
	// 		throw (CustomException("connect() error: cannot connect to hostname"));
	// 	isConnected = true;
	// }
	// else
	// 	cout << "Client already connected" << endl;
	return (0);
}
