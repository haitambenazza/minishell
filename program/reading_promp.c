/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/21 16:21:59 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handl(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}

int	history(char *str)
{
	if (!str)
		return (1);
	add_history(str);
	// rl_clear_history();
	return (0);

}

void	cntl_D(void)
{
	rl_on_new_line();
	rl_redisplay();
}

int	reading_promp(void)
{
	t_shell	*shell;
	char	*inputs;

	signal(SIGINT, handler);
	signal(SIGQUIT, handl);
	while (1)
	{
		inputs = readline("minishell>");
		// if (!inputs)
		// 	cntl_D();
		shell = parsing(ft_strtrim(inputs, " "));
		if (history(inputs))
			return (free(inputs), 1);
		free(inputs);
		taha(shell);
	}
	return (0);
}
