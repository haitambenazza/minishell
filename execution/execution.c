/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:10:44 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/09 03:04:26 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	execute(t_shell *cmds)
// {
// 	int pid;

// 	pid = fork();
// 	if (pid == 0)
// 		execve("/usr/bin/ls", cmds->cmd, lst_arr(cmds));
// 	else
//         while (waitpid(pid, NULL, WUNTRACED) == -1);
// 	return (0);
// }

//void	open_

int	child_pross(t_shell *cmds)
{
	t_shell *tmp;
	char *new_cmd;
	char **envp;

	tmp = cmds;
	envp = lst_arr(tmp);
	new_cmd = get_cmd(tmp->cmd[0] ,envp);
	if (is_built_in(cmds))
	{
		if (execve(new_cmd, tmp->cmd, envp) == -1)
		{
			perror(tmp->cmd[0]);
			clean_up(tmp);
			free_array(envp);
			exit(127);
			return (1);
		}
	}
	else
	{
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
// int	execute(t_shell *cmds)
// {
// 	t_shell	*tmp;

// 	tmp = cmds;
// 	tmp->cmd_count = cmds_size(tmp);
// 	index_nodes(tmp);
// 	tmp->pid = fork();
// 	if (!tmp->pid && is_built_in(cmds))
// 		child_pross(tmp);
// 	else
// 		parent_proc(tmp);
// 	return (0);
// }
int	execute(t_shell *cmds)
{
	t_shell	*tmp;
	int	pipe_fd[2];

	tmp = cmds;
	if (pipe(pipe_fd) == -1)
		perror("ERROR");
	tmp->cmd_count = cmds_size(tmp);
	tmp = cmds;
	index_nodes(tmp);
	if (tmp->cmd_count >= 2)
	{
		puts("ha 2");
		tmp->pid = fork();
		if (!tmp->pid && is_built_in(cmds))
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			child_pross(tmp);
		}
		else
			parent_proc(tmp);
	}
	else
	{
		tmp->pid = fork();
		if (!tmp->pid)
			child_pross(tmp);
		else
			parent_proc(tmp);
	}
	return (0);
}
int execution(t_shell *cmds)
{
	t_shell *tmp;
	int 	save_fd;

	tmp = cmds;
	save_fd = 0;
	while (tmp)
	{
			if (tmp->redirection && (tmp->redirection->type == RED_OUT || tmp->redirection->type == APPEND))
				save_fd = dup(STDOUT_FILENO);
			else
				save_fd = dup(STDIN_FILENO);
			if (handel_redirection(tmp->redirection) == 0)
			{
				if (if_built_in_run(cmds) == 1)
				{
					if (tmp->cmd)
					{
						if (execute(tmp))
							return (1);
					}
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