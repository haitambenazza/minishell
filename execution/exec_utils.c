/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:12:25 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/23 21:28:41 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			return (free_array(arr), pathcmd);
		free(pathcmd);
		i++;
	}
	free_array(arr);
	return NULL;
}

void    simple_cmd(t_shell *tmp)
{
	pid_t	pid = 0;
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	pid = fork();
	if (!pid)
		child_pross(tmp);
	else
		parent_proc(tmp);
}

void pipe_line(t_shell *cmds)
{
    t_shell *tmp;
    int pipefd[2];
    int in_fd;
    int status;
    pid_t   pid;

    status = 0;
    pid = 0;
    tmp = cmds;
    in_fd = STDIN_FILENO;
    while (tmp)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(exit_status);
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(exit_status);
        }
        else if (pid == 0)
        {
            if (in_fd != STDIN_FILENO)
            {
                if (dup2(in_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(exit_status);
                }
                close(in_fd);
            }
            if (tmp->next != NULL)
            {
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(exit_status);
                }
                close(pipefd[1]);
            }
            close(pipefd[0]);
            child_pross(tmp);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(pipefd[1]);
            waitpid(pid, &status, 0);
            tmp = tmp->next;
            in_fd = pipefd[0];
        }
    }
}
