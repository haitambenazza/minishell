/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/11 17:17:24 by hbenazza         ###   ########.fr       */
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

int	reading_promp(void)
{
	t_shell	*shell;
	char	*inputs;

	signal(SIGINT, handler);
	signal(SIGQUIT, handl);
	while (1)
	{
		inputs = readline("minishell>");
		shell = parsing(inputs);
		if (history(inputs))
			return (1);
		free(inputs);
		taha(shell);
	}
	return (0);
}
