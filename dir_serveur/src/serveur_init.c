/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:33:48 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:33:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
** First function for the serveur initialization.
*/

int		init_serveur(t_serveur *serv)
{
	if (init_serveur_connection(serv) == 0)
	{
		clear_serveur(serv);
		print_serveur_datas(serv);
		return (0);
	}
	else
		return (-1);
}

int		init_serveur_connection(t_serveur *serv)
{
	int						sock;
	struct sockaddr_in		sin;
	int						optval;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (init_error("socket()"));
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(serv->port);
	sin.sin_family = AF_INET;
	optval = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
		return (init_error("setsockopt()"));
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (init_error("bind()"));
	if (listen(sock, LISTEN_MAX_CLIENTS) < 0)
		return (init_error("listen()"));
	ft_printfstr(KGRN "- Serveur connection init OK -\n" KRESET, NULL);
	serv->serveur_sock = sock;

	return (0);
}

int		init_error(char *error_source)
{
	ft_printfstr(KRED "[Serveur]:" KRESET, NULL);
	ft_printfstr("Error in %s function call.\n", error_source);
	return (-1);
}

/*
**	The serveur connection initialization (socket, listen, etc) is OK
**	Now we clean the server's variables.
*/

void	clear_serveur(t_serveur *serv)
{
	serv->is_running = 1;
	serv->sock_endpoint = serv->serveur_sock;
	serv->read_fd_set = (fd_set *)s_malloc((sizeof(fd_set)));
	serv->write_fd_set = (fd_set *)s_malloc((sizeof(fd_set)));
	serv->client_handler.nb_clients = 0;
	serv->client_handler.clients_list = NULL;
}

void	print_serveur_datas(t_serveur *serv)
{
	ft_printfstr(KGRN "\nServer datas:\n" KRESET, NULL);
	ft_printfstr("port: ", NULL);
	ft_putnbr(serv->port);
	ft_putchar('\n');
	ft_putchar('\n');
}