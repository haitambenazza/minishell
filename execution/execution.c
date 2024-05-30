/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/30 18:55:13 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_pipes(t_shell *cmd)
{
	if (!cmd)
		return;
	if (cmd->next == NULL)
	{
		cmd->input_fd = STDIN_FILENO;
		cmd->output_fd = STDOUT_FILENO;
	}
	else
	{
		cmd->next->input_fd = cmd->pipe_fd[1];
		cmd->output_fd = cmd->pipe_fd[0];
	}
}

void	*execution(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
	cmds->envp = lst_arr(tmp); //free_array(envir);

	if (tmp->redirection == NULL)
		//handel_redirection();
	if (tmp->next == NULL)
	{
		if (if_built_in_run(tmp))
			execute_cmd(tmp);
	}
	if (tmp->next != NULL)
		open_pipes(cmds);
	clean_up(cmds);
	return (NULL);
}

//test
	// for (t_shell *t = cmds; t; t=t->next)
	// {
	// 	for (t_redirect *l = t->redirection; l; l=l->next)
	// 	{
	// 		printf("cmd   %s\n", t->cmd[0]);
	// 		printf("redirection type of %u for file {%s}\n", l->type, l->file_name);
	// 	}
	// }