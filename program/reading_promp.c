/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/03 18:28:52 by tkoulal          ###   ########.fr       */
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
	node->infile = dup(0);
	node->outfile = dup(1);
}

void increment_shlvl(t_env *env, t_env *envp)
{
	t_env	*tmp;
	t_env	*tmp_cp;
	char	*n;

	tmp = env;
	tmp_cp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL"))
		{
			n = ft_itoa(ft_atoi(tmp->value) + 1);
			free(tmp->value);
			tmp->value = n;
		}
		tmp = tmp->next;
	}
	while (tmp_cp)
	{
		if (!ft_strncmp(tmp_cp->key, "SHLVL"))
		{
			n = ft_itoa(ft_atoi(tmp_cp->value) + 1);
			free(tmp_cp->value);
			tmp_cp->value = n;
		}
		tmp_cp = tmp_cp->next;
	}
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

int	reading_promp(char **env)
{
	t_shell	*shell;
	t_shell	*shell_tmp;
	t_env	*env_cp;
	t_env	*envp;
	char	*inputs;

	env_cp = create_lst_env(env);
	envp = create_lst_env(env);
	increment_shlvl(env_cp, envp);
	while (1337)
	{
		// signals();
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		inputs = readline("minishell~> ");
		if (!inputs)
			cntl_d(shell, envp, env_cp);
		signal(SIGINT, ctrl_b_s);
		signal(SIGQUIT, ctrl_b_slash);
		shell = parsing(ft_strtrim(inputs, " \t"), env_cp, envp);
		if (history(inputs))
			return (free(inputs), 3);
		free(inputs);
		if (shell)
		{
			shell_tmp = shell;
			if (execution(shell))
				return (g_exit_status);
		}
		clean_up(shell, 0);
	}
	return (0);
}
