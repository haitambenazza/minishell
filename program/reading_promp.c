/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/25 21:55:51 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line(" ", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	history(char *str)
{
	if (!str)
		return (1);
	add_history(str);
	return (0);

}
int	reading_promp(void)
{
	char	*inputs;

	signal(SIGINT, handler);
	while (1)
	{
		inputs = readline("minishell> ");
		parsing(inputs);
		history(inputs);
	}
	return (1);
}
