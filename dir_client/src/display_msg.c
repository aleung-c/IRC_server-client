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

void	display_public_msg(t_client *client, char *msg)
{
	int		arg1_pos;
	int		arg2_pos;
	int		arg3_pos;

	(void)client;
	arg1_pos = len_to_next_proto_arg(msg) + 2;
	printf("arg 1: %s\n", msg + arg1_pos);
	arg2_pos = arg1_pos + len_to_next_proto_arg(msg + arg1_pos) + 2;
	printf("arg 2: %s\n", msg + arg2_pos);
	arg3_pos = arg2_pos + len_to_next_proto_arg(msg + arg2_pos) + 2;
	printf("arg 3: %s\n", msg + arg3_pos);
}
