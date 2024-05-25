/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:37:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/24 23:51:50 by tkoulal          ###   ########.fr       */
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
	int		i;

	i = 0;
	while (shell->cmd[i])
		i++;
	if (i > 2)
		return (write(2, "pwd: too many arguments! \n", 26), 1);
	if (i == 1 || !ft_strncmp(shell->cmd[1], "~"))
	{
		home_path= getenv("HOME");
		if (chdir(home_path))
			return (perror("cd"), 1);
	}
	else if (chdir(shell->cmd[1]))
		return (perror("cd"), 1);
	return (0);
}

int	ft_export(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_env(t_env *shell)
{
	while (shell)
	{
		printf("%s=%s\n", shell->key, shell->value);
		shell = shell->next;
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	clean_up(shell);
	write(1, "exit\n", 5);
	exit(0);
}
