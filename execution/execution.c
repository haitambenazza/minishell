/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/22 18:24:14 by tkoulal          ###   ########.fr       */
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
	// for (t_shell *tmp = cmds; tmp; tmp=tmp->next)
	// {
	// 	for (int i=0; tmp->cmd[i]; i++)
	// 		printf("node nbr %d : %s \n",i , tmp->cmd[i]);
	// }

void	*taha(t_shell *cmds)
{
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
