/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/07 21:00:02 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_status = 0;

int run_execution(t_shell *cmds)
{
	int	err;
	// if (handle_heredoc(tmp) == -1)
	// {
	// 	//run_heredoc(tmp); TODO
	// 	return (2);
	// }
	if (cmds->next == NULL && !is_built_in(cmds))
	{
		err = if_built_in_run(cmds);
		if (err == 1)
			return (2);
		else if (err < 0)
			return (1);
	}
	if (run_execution1(cmds) == 1)
		return (ERROR);
	free_array(cmds->envp);
	close_fd(cmds->input_fd, cmds->output_fd);
	clean_up(cmds);
	return (SUCCESS);
}

int		run_execution1(t_shell *cmds)
{
	int			status;
	t_shell		*tmp;

	status = 0;
	tmp = cmds;
	cmds->envp = lst_arr(tmp);
	while (tmp)
	{
		if (execute(tmp) == SUCCESS)
			exit_status = 0;
		else
			close_fd(tmp->input_fd ,tmp->output_fd);
		tmp = tmp->next;
	}
	if (status == -1)
		return (ERROR);
	if (status == 13)
		status = 127;
	exit_status = status;

	return (SUCCESS);
}

int	execute(t_shell *cmds)
{
	t_shell		*tmp;
	t_redirect 	*tmp_redirection;
	int		pipe_fd[2];
	int		err;

	tmp = cmds;
	// int i = 0;
	tmp_redirection = cmds->redirection;
	cmds->pid = 0;
	// puts("command:");
	// while (tmp)
	// {
	// 	while (tmp->cmd[i] != NULL)
	// 		puts(tmp->cmd[i]),i++;
	// 	tmp = tmp->next;
	// }
	// puts("redirections:");
	// while (tmp_redirection)
	// {
	// 	printf("Type = %d\n", tmp_redirection->type);
	// 	tmp_redirection = tmp_redirection->next;
	// }

	
	if (tmp->next != NULL)
	{
		if (open_pipes(cmds, pipe_fd))
			return (ERROR);
	}
	while (tmp_redirection != NULL)
	{
		// printf(GREEN"should open  this file {%s} \n"RST, tmp_redirection->file_name);
		err = handel_redirection(tmp_redirection);
		if (err < 0)
		{
			exit_status = 1;
			return (err);
		}
		tmp_redirection = tmp_redirection->next;
	}
	if (execute_cmd(cmds) == ERROR)
		return (ERROR);
	return (0);
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