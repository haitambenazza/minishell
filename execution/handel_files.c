/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:55:13 by tkoulal           #+#    #+#             */
/*   Updated: 2024/06/30 15:11:38 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int open_infiles(t_redirect *node)
{
    int status;

    status = 0;
    if (!node->file_name)
    {
        printf(RED "minishell: ambiguous redirect\n" RST);
        return (-1);
    }
    // status = check_infile_access(node->file_name);
    if (status < 0)
        return (ERROR);
    return (status);
}
int open_outfiles(char *file)
{
    int status;

    status = 0;
    status = open(file, O_WRONLY | O_APPEND | O_CREAT, 0640);
    return (status);
}

int handel_redirection(t_redirect *node)
{
    int fd;
    while (node)
    {
        if (node->type == RED_OUT)
        {
            fd = open(node->file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
            if (fd < 0)
            {
                perror(node->file_name);
                close(fd);
                return (1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        else if (node->type == RED_IN)
        {
            if (access(node->file_name, R_OK) == 0)
            {
                fd = open(node->file_name, O_RDONLY);
                if (fd < 0)
                {
                    perror(node->file_name);
                    close(fd);
                    return (1);
                }
                dup2(fd, STDIN_FILENO);
            }
            else
            {
                perror(node->file_name);
                return (1);
            }
        }
        else if (node->type == APPEND)
        {
            fd = open(node->file_name, O_RDWR | O_CREAT | O_APPEND, 0666);
            if (fd < 0)
            {
                perror(node->file_name);
                close(fd);
                return (1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        node = node->next;
    }
    return (0);
}