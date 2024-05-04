/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/04 17:25:56 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_up(t_shell *shell);
void	free_array(char **v);

void	*taha(t_shell *cmds)
{
	//here you can work on execution fetch the commands with tmp->cmd[i]
	t_shell	*tmp;

	tmp = cmds;
	while (tmp)
	{
		printf("%s\n", tmp->cmd[0]);
		tmp = tmp->next;
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
	free(tmp->token);
	while (tmp)
	{
		free_array(tmp->cmd);
		tmp = tmp->next;
		free(shell);
		shell = tmp;
	}
}
