/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:46:50 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/04 12:21:30 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals()
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_d_her(void)
{
	g_exit_status = 0;
	write(1, "minishell: you have exited without specifying a delimeter\n", 58);
}

void	cntl_d(t_shell *sh, t_env *env, t_env *envp)
{
	(void)sh;
	rl_on_new_line();
	rl_clear_history();
	write(1, "exit\n", 5);
	clean_lst(env);
	clean_lst(envp);
	exit(g_exit_status);
}
