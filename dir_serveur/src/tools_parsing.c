/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:09:29 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/27 17:09:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

char	**string_lexer(char *msg, char delim)
{
	int		i;
	int		nb_words;
	char	**ret;

	i = 0;
	ret = NULL;
	nb_words = str_word_count(msg, delim);
	if (nb_words == 0)
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *) * nb_words + 1)))
		exit(-1);
	ret[nb_words] = NULL;
	fill_array(ret, msg, delim, nb_words);
	return (ret);
}

int		str_word_count(char *msg, char delim)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (msg[i])
	{
		if (msg[i] && msg[i] != delim)
		{
			ret += 1;
			while (msg[i] && msg[i] != delim)
				i++;
		}
		if (msg[i] && (msg[i] == delim))
		{
			while (msg[i] && (msg[i] == delim))
				i++;
		}
	}
	return (ret);
}

void	fill_array(char **array, char *msg, char delim, int nb_words)
{
	int		i;
	int		y;
	int		array_count;

	i = 0;
	y = 0;
	array_count = 0;
	while (msg[i] && array_count < nb_words)
	{
		if (msg[i] && msg[i] != delim)
		{
			y = 0;
			while (msg[i + y] && msg[i + y] != delim)
				y++;
			if (!(array[array_count] = (char *)malloc(sizeof(char) * y)))
				exit(-1);
			ft_memcpy(array[array_count], msg + i, y);
			array[array_count][y] = '\0';
			array_count++;
			i += y;
		}
		while (msg[i] && (msg[i] == delim))
			i++;
	}
}

int		get_array_count(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_lexed_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
