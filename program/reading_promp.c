/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/25 12:43:19 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	history(char *str)
{
	if (!str)
		return (1);
	if (ft_strlen(str))
		add_history(str);
	return (0);

}

void	set_hold(t_shell *node)
{
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
}

int	reading_promp(char **env)
{
	t_shell	*shell;
	char	*inputs;
	int err;

	err = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_empty);
	err = 0;
	while (1337)
	{
		inputs = readline("minishell~> ");
		if (!inputs)
			cntl_D();
		shell = parsing(ft_strtrim(inputs, " \t"), env);
		if (history(inputs))
			return (free(inputs), 3);
		free(inputs);
		if (shell)
			set_hold(shell);
		if (shell)
			err = execution(shell);
		if (err < 0)
			return (1);
		clean_up(shell);
	}
	return (0);
}
