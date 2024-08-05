/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:16:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/04 20:07:50 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_her(int signal)
{
	g_exit_status = 130;
	if (signal == SIGINT)
	{
		exit(130);
	}
}

void	ctrl_b_slash(int signal)
{
	(void)signal;
	printf("Quit\n");
}

void	ctrl_b_s(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}
