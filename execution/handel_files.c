/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:55:13 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/27 22:49:57 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_infile_acces(char *file_name)
{
	int	status;

	status = access(file_name, F_OK);
	if (status == -1)
    {
        perror(file_name);
		return (-1);
    }
	else
	{
		status = open(file_name, O_RDONLY);
		if (status == -1)
        {
            perror(file_name);
			return (-1);
        }
		else
			return (status);
	}
	return (ERROR);
}

int	open_infiles(t_shell *node)
{
	int	status;

	status = check_infile_acces(node->redirection->file_name);
	if (status < 0)
		return (status);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	node->infile = status;
	return (SUCCESS);
}

int open_outfiles(t_shell *node)
{
	t_redirect	*tmp;
    int status;
    int flags;

    status = 0;
    flags = 0;
	tmp = node->redirection;
	while (tmp)
	{
		if (tmp->type == 4)
			flags = O_TRUNC;
		else if (tmp->type == 11)
			flags = O_APPEND;
		flags = O_WRONLY | O_CREAT;
		status = open(tmp->file_name, flags, 0644);
		if (status < 0)
		{
			if (access(tmp->file_name, F_OK) == -1)
			{
				perror(tmp->file_name);
				g_exit_status = 20;
				close(status);
				return (g_exit_status);
			}
		}
		if (node->outfile != STDOUT_FILENO)
			close(node->outfile);
		node->outfile = status;
		tmp = tmp->next;
	}
    return (status);
}

int	check_is_valid_redirection(t_redirect *tmp_red)
{
	if (!ft_strlen(tmp_red->file_name))
	{
		g_exit_status = 1;
		printf("minishell:%s ambiguous redirect \n",tmp_red->file_name);
		return (g_exit_status);
	}
	return (0);
}

int handel_redirection(t_shell *node)
{
    t_redirect *tmp_red;

    tmp_red = node->redirection;
	if (check_is_valid_redirection(tmp_red))
		return (g_exit_status);
    while (tmp_red)
    {
        if (tmp_red->type == RED_OUT || tmp_red->type == APPEND) // >
        {
            if (open_outfiles(node) < 0)
                return (ERROR);
        }
        else if (tmp_red->type == RED_IN)// <
        {
            if (open_infiles(node) < 0)
                return (ERROR);
        }
        else if (tmp_red->type == 13)
        {
            // if (open_herdoc(node) < 0)
                return (ERROR);
        }
        tmp_red = tmp_red->next;
    }
    return (0);
}
