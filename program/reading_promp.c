/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/28 18:45:41 by hbenazza         ###   ########.fr       */
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
	t_env	*env_cp;
	t_env	*envp;
	char	*inputs;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_empty);
	env_cp = create_lst_env(env);
	envp = create_lst_env(env);
	while (1337)
	{
		inputs = readline("minishell~> ");
		if (!inputs)
			cntl_d(shell, envp, env_cp);
		shell = parsing(ft_strtrim(inputs, " \t"), env_cp, envp);
		if (history(inputs))
			return (free(inputs), 3);
		free(inputs);
		if (shell)
		{
			set_hold(shell);
			if (execution(shell))
				return (g_exit_status);
		}
		clean_up(shell, 0);
	}
	return (0);
}
