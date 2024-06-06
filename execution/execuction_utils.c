/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuction_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:57:51 by tkoulal           #+#    #+#             */
/*   Updated: 2024/06/06 13:51:14 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	open_pipes(t_shell *cmd, int pipe_fd[2])
{
	if (!cmd)
		return (ERROR);
	if (pipe(pipe_fd) == -1)
	{
		printf(RED"minishell: pipe: %s\n"RST, strerror(errno));
		//g_data.exit_status = 1;
		return (ERROR);
	}
	if (cmd->next == NULL)
	{
		cmd->input_fd = STDIN_FILENO;
		cmd->output_fd = STDOUT_FILENO;
	}
	else
	{
		cmd->next->input_fd = pipe_fd[0];
		cmd->output_fd = pipe_fd[1];
	}
	return (SUCCESS);
}

int		close_fd(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (SUCCESS);
}

int	handle_heredoc(t_shell *cmds)
{
	int	fd;
	t_shell	*node;

	fd = 0;
	node = cmds;
	while (node->redirection != NULL)
	{
		if (node->redirection->type == 13)
		{
			//fd = ft_heredoc(readline, l_env, node->file_name[i]); TODO
            if (fd == -1)
                return (fd);
		}
		node->redirection = node->redirection->next;
	}
	return (SUCCESS);
}