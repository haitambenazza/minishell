/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/24 13:18:46 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin(t_shell *cmds, t_env *env)
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
		else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "export"))
			ft_export(tmp, env);
		else
			excute_cmd(cmds, env);
		tmp= tmp->next;
		i++;
	}
}

void	*execute(t_shell *cmds, t_env *env)
{
	builtin(cmds, env);
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

void	clean_lst(t_env *shell)
{
	t_env	*lst;

	lst = shell;
	while (shell)
	{
		lst = shell->next;
		free(shell);
		shell = lst;
	}
}

void	clean_up(t_shell *shell)
{
	t_shell	*tmp;

	tmp = shell;
	if (shell->mask)
		free(shell->mask);
	if (shell->token)
		free(shell->token);
	// if (shell)
	// 	clean_lst(shell->env);
	while (tmp)
	{
		if (tmp->cmd)
			free_array(tmp->cmd);
		tmp = tmp->next;
		free(shell);
		shell = tmp;
	}
}
