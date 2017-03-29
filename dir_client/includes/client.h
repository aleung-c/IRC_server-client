/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:27:15 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:27:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include "../../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <time.h>

/*
**	color in text;
*/

# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"
# define KRESET "\x1B[0m"

# define HOSTNAME_MAX_LEN 255

# define BUFFER_SIZE 4096
# define MSG_SIZE 512 // default 512

# define PROTOCOL_MAX_MSG_SIZE 10
# define CMD_MAX_LEN 10

# define MAX_NICK_LEN 9
# define MAX_CHANNEL_NAME_LEN 50
# define MAX_JOINABLE_CHAN 5

/*
**	Server structs.
*/

# include "client_main_struct.h"

/*
** ----- Function prototypes
*/

int				input_args_handling(t_client *client, int argc, char **argv);
void			print_usage(char *arg);

int				get_hostname(t_client *client, char *arg);
int				get_port(t_client *client, char *arg);

#endif
