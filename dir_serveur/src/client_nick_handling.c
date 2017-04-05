/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_nick_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 16:41:41 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/29 16:41:44 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	Return the client from the corresponding nick,
**	from the server's global list.
*/

t_client	*get_client_by_nick(t_serveur *serv, char *nick)
{
	t_client	*tmp;

	tmp = serv->client_handler.clients_list;
	while (tmp)
	{
		if (ft_strncmp(nick, tmp->nickname,
			ft_strlen(tmp->nickname)) == 0
			&& ft_strlen(nick) == ft_strlen(tmp->nickname))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int			nick_has_forbidden_chars(char *nick)
{
	int i;

	i = 0;
	while (nick[i])
	{
		if (ft_isalnum(nick[i]) != 1
			&& nick[i] != '-'
			&& nick[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
