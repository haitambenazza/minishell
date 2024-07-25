/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:55:13 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/25 15:45:22 by tkoulal          ###   ########.fr       */
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
    int status;
    int flags;

    status = 0;
    flags = 0;
    
    if (node->redirection->type == 4)
        flags |= O_TRUNC;
    else if (node->redirection->type == 11)
        flags |= O_APPEND;
    flags |= O_WRONLY | O_CREAT;
    status = open(node->redirection->file_name, flags, 0644);
    if (status < 0)
    {
        status = access(node->redirection->file_name, F_OK);
        if (status == -1)
        {
            perror(node->redirection->file_name);
            close(status);
            return (ERROR); 
        }
    }
    if (node->outfile != STDOUT_FILENO)
        close(node->outfile);
    node->outfile = status;
    return (status);
}

int handel_redirection(t_shell *node)
{
    t_redirect *tmp_red;

    tmp_red = NULL;
    while (node->redirection)
    {

        tmp_red = node->redirection;
        if (node->redirection->type == 4 || node->redirection->type == 11) // >
        {
            if (open_outfiles(node) < 0)
                return (ERROR);
        }
        else if (node->redirection->type == 3)// <
        {
            if (open_infiles(node) < 0)
                return (ERROR);
        }
        else if (node->redirection->type == 13)
        {
            if (open_outfiles(node) < 0)
                return (ERROR);
        }
        node->redirection = node->redirection->next;
    }
    return (0);
}