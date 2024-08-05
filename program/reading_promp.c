/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/05 13:53:48 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	history(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			flag = 1;
		i++;
	}
	if (ft_strlen(str) && flag && str)
		add_history(str);
	free(str);
	return (0);
}

void	set_hold(t_shell *node)
{
	node->infile = dup(0);
	node->outfile = dup(1);
}

int	increment_shlvl(t_env *env, t_env *envp)
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
			return (free(tmp->value), tmp->value = n, 1);
		}
		tmp = tmp->next;
	}
	while (tmp_cp)
	{
		if (!ft_strncmp(tmp_cp->key, "SHLVL"))
		{
			n = ft_itoa(ft_atoi(tmp_cp->value) + 1);
			return (free(tmp_cp->value), tmp_cp->value = n, 1);
		}
		tmp_cp = tmp_cp->next;
	}
	return (0);
}

int	reading_promp(char **env)
{
	t_shell	*shell;
	t_env	*env_cp;
	t_env	*envp;
	char	*inputs;

	env_cp = create_lst_env(env);
	envp = create_lst_env(env);
	increment_shlvl(env_cp, envp);
	while (1337)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		inputs = readline("minishell~> ");
		if (!inputs)
			cntl_d(shell, envp, env_cp);
		signal(SIGINT, ctrl_b_s);
		signal(SIGQUIT, ctrl_b_slash);
		shell = parsing(ft_strtrim(inputs, " \t"), env_cp, envp);
		history(inputs);
		if (execution(shell))
			return (g_exit_status);
		clean_up(shell, 0);
	}
	return (0);
}
