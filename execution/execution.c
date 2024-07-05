/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:10:44 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/05 18:54:16 by tkoulal          ###   ########.fr       */
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

char    **find_path(char **envp)
{
    int    i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strnncmp(envp[i], "PATH=", 5))
            return (ft_split(envp[i] + 5, ":"));
        i++;
    }
    return (NULL);
}

char *get_cmd(char *cmd, char **envp)
{
    char **arr;
    char *pathcmd;
    char *tmp_pathcmd;
    int i;

    i = 0;
    if (ft_strchr(cmd, '/'))
	{
        if (access(cmd, F_OK | X_OK) != -1)
            return (ft_strdup(cmd));
        return (NULL);
    }
    arr = find_path(envp);
    if (!arr)
        return (printf("path not found\n"), exit(EXIT_FAILURE), NULL);

    while (arr[i] && arr)
    {
        tmp_pathcmd = ft_strjoin("/", cmd);
        pathcmd = ft_strjoin(arr[i], tmp_pathcmd);
        free(tmp_pathcmd);
        if (access(pathcmd, F_OK | X_OK) != -1)
        {
            free_array(arr);
            return (pathcmd);
        }
        free(pathcmd);
        i++;
    }
    free_array(arr);
    return NULL;
}

//void	open_

int	child_pross(t_shell *cmds)
{
	t_shell *tmp;
	char *new_cmd;

	tmp = cmds;
	new_cmd = get_cmd(tmp->cmd[0] ,lst_arr(tmp));
	if (execve(new_cmd, tmp->cmd, lst_arr(tmp)) == -1)
	{
		perror(tmp->cmd[0]);
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
	t_shell	*tmp;
	// int		pipe_fd[2];

	tmp = cmds;
	tmp->cmd_count = cmds_size(tmp);
	// open_pipes(pipefds, tmp);
	// pipe(pipe_fd);
	tmp->pid = fork();
	// dup2(STDOUT_FILENO, pipe_fd[1]);
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