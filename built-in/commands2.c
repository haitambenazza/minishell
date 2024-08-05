/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:02:56 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/05 13:33:58 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_shell *sh)
{
	t_env	*envp;
	t_env	*envp_cp;
	int		i;

	envp = sh->env;
	envp_cp = sh->env_copy;
	i = 1;
	while (sh->cmd[i])
	{
		if (is_in_env(sh, sh->cmd[i], 0))
			remove_from_export(sh, sh->cmd[i]);
		if (is_in_env(sh, sh->cmd[i], 1))
			remove_from_env(sh, sh->cmd[i]);
		i++;
	}
	return (0);
}

void	exit_failing_msg(void)
{
	write(2, "minishell: invalid argument, takes only integers\n", 49);
	exit(2);
}

int	ft_exit(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->cmd[1])
	{
		while (shell->cmd[1])
		{
			if (shell->cmd[1][i] < '0' || shell->cmd[1][i] > '9')
				exit_failing_msg();
			i++;
		}
		g_exit_status = ft_atoi(shell->cmd[1]);
	}
	clean_up(shell, 1);
	write(1, "exit\n", 5);
	exit(g_exit_status);
}

char	*ft_getenv(char *s, t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, s))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

int	go_home_dir(t_shell *sh, char *old_pwd)
{
	char	*home;

	home = ft_getenv("HOME", sh);
	if (chdir(home))
	{
		free(home);
		return (perror("cd"), free(old_pwd), g_exit_status = 1, 1);
	}
	get_old_dir(sh, old_pwd);
	set_current_dir(sh);
	free(home);
	free(old_pwd);
	g_exit_status = 0;
	return (0);
}
