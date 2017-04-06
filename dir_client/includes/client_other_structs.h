/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_other_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:46:10 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/30 18:46:12 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_OTHER_STRUCTS_H
# define CLIENT_OTHER_STRUCTS_H

# include "client.h"

/*
** ----- Circular buffer
*/

typedef struct				s_circular_buffer
{
	int						is_waiting;
	char					data[BUFFER_SIZE];
	int						start;
	int						end;
	int						len;
}							t_circular_buffer;

#endif
