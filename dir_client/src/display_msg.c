/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 10:50:29 by aleung-c          #+#    #+#             */
/*   Updated: 2017/03/31 10:50:30 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

/*
**	My protocol delimiting always with"::", i display by moving through these
**	"::". That is why the syntax is peculiar.
*/

void	display_public_msg(t_client *client, char *msg)
{
	int		arg1_pos;
	int		arg2_pos;
	int		arg3_pos;

	(void)client;
	arg1_pos = len_to_next_proto_arg(msg) + 2;
	arg2_pos = arg1_pos + len_to_next_proto_arg(msg + arg1_pos) + 2;
	arg3_pos = arg2_pos + len_to_next_proto_arg(msg + arg2_pos) + 2;

	printf("[%s%.*s%s] %s%.*s%s: %s\n", KCYN,
		arg2_pos - arg1_pos - 2, msg + arg1_pos, KRESET, KYEL,
		arg3_pos - arg2_pos - 2, msg + arg2_pos, KRESET,
		msg + arg3_pos);
}

void	display_private_msg(t_client *client, char *msg)
{
	int		arg1_pos;
	int		arg2_pos;

	(void)client;
	arg1_pos = len_to_next_proto_arg(msg) + 2;
	arg2_pos = arg1_pos + len_to_next_proto_arg(msg + arg1_pos) + 2;
	

	printf("(%sWhisper%s %s>>>>%s %s%.*s%s): %s\n", KCYN, KRESET, KBLU, KRESET,
		KYEL, arg2_pos - arg1_pos - 2, msg + arg1_pos, KRESET,
		msg + arg2_pos);
}

void	display_error_msg(t_client *client, char *msg)
{
	int		arg1_pos;

	(void)client;
	arg1_pos = len_to_next_proto_arg(msg) + 2;
	printf(KMAG "[Server error]%s: %s\n", KRESET, msg + arg1_pos);
}