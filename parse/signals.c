/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:46:50 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 20:11:08 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	cntl_D(t_shell *sh, t_env *env, t_env *envp)
{
	(void)sh;
	rl_on_new_line();
	rl_clear_history();
	write(1, "exit\n", 5);
	clean_lst(env);
	clean_lst(envp);
	exit(exit_status);
}

void	ctrl_empty(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}
