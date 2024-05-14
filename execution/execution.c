/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/14 11:53:45 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_up(t_shell *shell);
void	free_array(char **v);

void	*taha(t_shell *cmds)
{
	//here you can work on execution fetch the commands with tmp->cmd[i]
	t_shell	*tmp;
	int		i;

	tmp = cmds;
	i = 0;
	if (!cmds)
		return (NULL);
	while (tmp)
	{
		if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "pwd"))
			ft_pwd(tmp);
		if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "exit"))
			ft_exit(tmp);
		tmp = tmp->next;
		i++;
	}
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
