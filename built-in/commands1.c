/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:37:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/23 19:25:31 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*dir;
	int		i;

	i = 0;
	while (shell->cmd[i])
		i++;
	if (i > 1)
		return (write(2, "pwd: too many arguments! \n", 26), 1);
	dir = getcwd((void *)0, 0);
	if (dir)
		printf("%s\n", dir);
	else
		return (perror("pwd"), 1);
	free(dir);
	return (0);
}

int	ft_cd(t_shell *shell)
{
	char	*home_path;
	char	*args;

	args = NULL;
	if (shell->cmd)
		args = ft_strjoin2(lst_size(shell->cmd + 1), shell->cmd + 1, "");
	if (!ft_strncmp(args, "~") || lst_size(shell->cmd) == 1)
	{
		home_path= getenv("HOME");
		if (chdir(home_path))
			return (perror("cd"), 2);
	}
	else if (chdir(args))
		return (perror("cd"), 2);
	return (0);
}

int	ft_export(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_env(t_env *shell)
{
	t_env	*tmp;

	tmp = shell;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	clean_up(shell);
	write(1, "exit\n", 5);
	exit(exit_status);
}
