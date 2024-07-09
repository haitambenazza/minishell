/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:10:44 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/09 01:08:44 by tkoulal          ###   ########.fr       */
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
	// int	status2;
	// int	term_signal;

	// status2 = 0;
	waitpid(tmp->pid, &status, 0);
	return (status);
}

int	execute(t_shell *cmds)
{
	// bda khdma mn hna !
	t_shell	*tmp;

	tmp = cmds;
	tmp->cmd_count = cmds_size(tmp);
	tmp->pid = fork();
	if (!tmp->pid && is_built_in(cmds))
		child_pross(tmp);
	else
		parent_proc(tmp);
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