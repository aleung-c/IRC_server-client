/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 20:37:28 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 20:37:29 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_MAIN_STRUCT_H
# define CLIENT_MAIN_STRUCT_H

# include "client.h"

/*
** ----- client Main Struct -----
*/

typedef struct				s_client
{
	char					*hostname;
	int						is_port_set;
	int						port;

	int						is_running;

	int						client_sock;
	int						sock_endpoint;

	fd_set					*read_fd_set;
	fd_set					*write_fd_set;
}							t_client;

#endif