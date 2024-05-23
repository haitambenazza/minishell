/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/23 11:54:36 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin(t_shell *cmds)
{
	int		i;
	t_shell	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "pwd"))
			ft_pwd(tmp);
		else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "exit"))
			ft_exit(tmp);
		else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "cd"))
			ft_cd(tmp);
		else
			excute_cmd(cmds);
		tmp= tmp->next;
		i++;
	}
}

void	*execute(t_shell *cmds, char **env)
{
	(void)env;
	if (!cmds)
		return (NULL);
	builtin(cmds);
	clean_up(cmds);
	return (NULL);
}

void	free_array(char **v)
{
	int	i;

	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	clean_up(t_shell *shell)
{
	t_shell	*tmp;

	tmp = shell;
	if (shell->mask)
		free(shell->mask);
	if (shell->token)
		free(shell->token);
	while (tmp)
	{
		if (tmp->cmd)
			free_array(tmp->cmd);
		tmp = tmp->next;
		free(shell);
		shell = tmp;
	}
}
