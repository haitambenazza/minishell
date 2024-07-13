/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/13 10:59:26 by hbenazza         ###   ########.fr       */
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

int	reading_promp(char **env)
{
	t_shell	*shell;
	char	*inputs;
	int		err;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_empty);
	err = 0;
	while (1337)
	{
		inputs = readline(GREEN"minishell~> "RST);
		if (!inputs)
			return (cntl_D(), 0);
		shell = parsing(ft_strtrim(inputs, " "), env);
		if (history(inputs))
			return (free(inputs), 1);
		free(inputs);
		for (t_shell *t = shell; t; t = t->next)
		{
			for (int i = 0; t->cmd[i]; i++)
				printf("%s final cmd\n", t->cmd[i]);
		}
		// if (shell)
		// 	err = execution(shell);
		// if (err < 0)
		// 	return (1);
		clean_up(shell);
	}
	return (0);
}
