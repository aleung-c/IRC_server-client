/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:07:44 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/17 16:19:16 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

int		main(int argc, char **argv)
{
	t_serveur	serv;

	if ((get_args(&serv, argc, argv)) == 0
		&& init_serveur(&serv) == 0)
	{
		serveur_main_loop(&serv);
		return (0);
	}
	else
	{
		return (-1);
	}
	return (0);
}
