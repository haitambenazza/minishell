/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:16:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/04 13:38:09 by tkoulal          ###   ########.fr       */
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

void	signal01()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_b_slash(int signal)
{
	(void)signal;

	printf("Quit (core dumped)\n");
}

void	ctrl_b_s(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}
