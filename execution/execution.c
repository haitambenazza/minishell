/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:10:44 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/25 13:14:19 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_builtins_pipe(t_shell *node)
{
	int	err;

	err = if_built_in_run(node);
	if (err)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	child_pross(t_shell *node, char **envp, char *new_cmd)
{
	signal(SIGQUIT, SIG_DFL);
	ft_dup2(node);

	if (node->next)
		if (node->next->infile != STDIN_FILENO)
			close(node->next->infile);
	if (!is_built_in(node))
		exit(run_builtins_pipe(node));
	if (execve(new_cmd, node->cmd, envp) == -1)
	{
		perror(node->cmd[0]);
		clean_up(node);
		free_array(envp);
		exit(127);
		return (1);
	}
	return (0);
}

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}
// ls | ifconfig
int	open_pipes(t_shell *node, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		printf("minishell: pipe: %s\n", strerror(errno));
		exit_status = 1;
		return (ERROR);
	}
	node->next->infile = pipe_fd[0];
	node->outfile = pipe_fd[1];
	return (SUCCESS);
}

void	ft_dup2(t_shell *node)
{
	if (dup2(node->infile, STDIN_FILENO) == -1)
	{
		printf("minishell: dup2: %s\n", strerror(errno));
		exit_status = 1;
		clean_up(node);
		exit(EXIT_FAILURE);
	}
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (dup2(node->outfile, STDOUT_FILENO) == -1)
	{
		printf("minishell: dup2: %s\n", strerror(errno));
		exit_status = 1;
		clean_up(node);
		exit(EXIT_FAILURE);
	}
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
}

int	execute_cmd(t_shell *node)
{
	char **envp;
	char *new_cmd;

	envp = lst_arr(node);
	new_cmd = get_cmd(node->cmd[0] ,envp);
	if (!new_cmd)
	{
		printf("%s :command not found\n", node->cmd[0]);
		free_array(envp);
		exit_status = 127;
		return (ERROR);
	}
	node->pid = fork();
	if (node->pid < 0)
	{
		printf("minishell: fork: %s\n", strerror(errno));
		exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (node->pid == 0)
		if (child_pross(node, envp, new_cmd) == 1)
			return (1);
	free_array(envp);
	free(new_cmd);
	return (SUCCESS);
}

int	execute(t_shell *node)
{
	int	pipe_fd[2];
	int	status;

	node->pid = 0;
	status = 0;
	if (node->next != NULL)
	{
		if (open_pipes(node, pipe_fd) == ERROR)
			return (ERROR);
	}
	else
		node->outfile = STDOUT_FILENO;
	if (node->redirection != NULL)
	{
		status = handel_redirection(node);
		if (status < 0)
		{
			exit_status = 1;
			return (status);
		}
	}
	if (execute_cmd(node) == ERROR)
		return (ERROR);
	close_fd(node->infile, node->outfile);
	return (SUCCESS);
}
int	run_exec(t_shell *cmds)
{
	t_shell	*tmp;
	int status;
	int size;
	int	i;

	size = cmds_size(cmds);
	tmp = cmds;
	status = 0;
	i = -1;
	while (tmp)
	{
		exit_status = 0;
		if (execute(tmp) == 0)
			exit_status = 0;
		else
		{
			exit_status = 127;
			close_fd(tmp->infile, tmp->outfile);
		}
		tmp = tmp->next;
	}
	tmp = cmds;
	while (tmp && tmp->next)
		tmp = tmp->next;
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status) && size > 1)
		exit_status = WEXITSTATUS(status);
	while (++i < size - 1)
		wait(NULL);
	printf("%d \n", exit_status);
	return (0);
}

int	execution(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
	tmp->pid = 0;
	if (cmds->next == NULL && !is_built_in(cmds) && !cmds->redirection)
	{
		if_built_in_run(cmds); // exec builtin
		return (0);
	}
	else if (run_exec(cmds) == ERROR)
	{
		return (ERROR);
	}
	return (0);
}
