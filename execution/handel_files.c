/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:55:13 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/23 22:49:49 by tkoulal          ###   ########.fr       */
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

    status = 0;
    status = open(node->redirection->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
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
    while (node->redirection)
    {
        if (node->redirection->type == 4) // >
        {
            if (open_outfiles(node) < 0)
                return (ERROR);
        }
        else if (node->redirection->type == 3)// <
        {
            if (open_infiles(node) < 0)
                return (ERROR);
        }
        // else if (node->type = 11)
        // {
        //     if (open_outfiles(node) < 0)
        //         return (ERROR);
        // }
        node->redirection = node->redirection->next;
    }
    return (0);
}







































































        // if (node->type == RED_OUT)
        // {
        //     fd = open(node->file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
        //     if (fd < 0)
        //     {
        //         perror(node->file_name);
        //         close(fd);
        //         return (1);
        //     }
        //     dup2(fd, STDOUT_FILENO);
        // }
        // else if (node->type == RED_IN)
        // {
        //     if (access(node->file_name, R_OK) == 0)
        //     {
        //         fd = open(node->file_name, O_RDONLY);
        //         if (fd < 0)
        //         {
        //             perror(node->file_name);
        //             close(fd);
        //             return (1);
        //         }
        //         dup2(fd, STDIN_FILENO);
        //     }
        //     else
        //     {
        //         perror(node->file_name);
        //         return (1);
        //     }
        // }
        // else if (node->type == APPEND)
        // {
        //     fd = open(node->file_name, O_RDWR | O_CREAT | O_APPEND, 0666);
        //     if (fd < 0)
        //     {
        //         perror(node->file_name);
        //         close(fd);
        //         return (1);
        //     }
        //     dup2(fd, STDOUT_FILENO);
        // }