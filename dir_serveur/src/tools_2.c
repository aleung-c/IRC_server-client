/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:07:36 by aleung-c          #+#    #+#             */
/*   Updated: 2017/04/05 18:07:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

/*
**	Get length until first delimiter c. Does not check boundaries!!
**	Best used after most size checks.
*/

int		get_len_to_delim(char *msg, char c)
{
	int i;

	i = 0;
	while (msg[i] && msg[i] != c)
	{
		if (msg[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	turn_tabs_to_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
		{
			str[i] = ' ';
		}
		i++;
	}
}

/*
**	Turn the last nl char to zero in a string.
*/

void	turn_nl_to_zero(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
		}
		i++;
	}
}
