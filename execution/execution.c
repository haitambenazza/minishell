/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:10:44 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/09 11:11:34 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_pross(t_shell *cmds)
{
	t_shell *tmp;
	char *new_cmd;
	char **envp;

	tmp = cmds;
	envp = lst_arr(tmp);
	new_cmd = get_cmd(tmp->cmd[0] ,envp);
	if (execve(new_cmd, tmp->cmd, envp) == -1)
	{
		perror(tmp->cmd[0]);
		clean_up(tmp);
		free_array(envp);
		exit(127);
		return (1);
	}
	return (0);
}

int	parent_proc(t_shell *tmp)
{
	int	status;

	status = 0;
	waitpid(tmp->pid, &status, 0);
	return (status);
}

void	index_nodes(t_shell *nodes)
{
	t_shell	*tmp;
	int		i;

	tmp = nodes;
	i = 0;
	while (tmp)
	{
		tmp->cmd_index = i;
		i++;
		tmp = tmp->next;
	}
}

int	execute(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
	if (tmp->cmd_count >= 2)
		pipe_line(tmp);
	else if(tmp->cmd_count == 1)
		simple_cmd(tmp);
	return (0);
}



int execution(t_shell *cmds)
{
	t_shell *tmp;
	int 	save_fd;

	tmp = cmds;
	save_fd = 0;
	tmp->pid = 0;
	tmp->cmd_count = cmds_size(tmp); //count how many command (node)
	while (tmp)
	{
		//handel_builtin();
		if (tmp->redirection && (tmp->redirection->type == RED_OUT || tmp->redirection->type == APPEND))
			save_fd = dup(STDOUT_FILENO);
		else
			save_fd = dup(STDIN_FILENO);
		handel_redirection(tmp->redirection);
		if (is_built_in(cmds) == 1)
		{
			if (tmp->cmd)
			{
				if (execute(tmp))
					return (1);
			}
		}
		if (tmp->redirection && (tmp->redirection->type == RED_OUT || tmp->redirection->type == APPEND))
			dup2(save_fd, STDOUT_FILENO);
		else
			dup2(save_fd, STDIN_FILENO);
		tmp = tmp->next;
	}
	return (0);
}