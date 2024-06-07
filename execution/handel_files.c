/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:55:13 by tkoulal           #+#    #+#             */
/*   Updated: 2024/06/07 20:56:05 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int open_infiles(t_redirect *node)
{
    int status;

    status = 0;
    if (!node->file_name)
    {
        printf(RED"minishell: ambiguous redirect\n"RST);
        return (-1);
    }
   // status = check_infile_access(node->file_name);
    if (status < 0)
        return (ERROR);
    return (status);
}
int open_outfiles(t_redirect *node)
{
    int status;

    status = 0;
    if (!node->file_name)
    {
        printf(RED"minishell: ambiguous redirect\n"RST);
        return (-1);
    }
    status = open(node->file_name, O_RDONLY);
    return (status);
}

int handel_redirection(t_redirect *node)
{
	int	i;

	i = -1;
    if (node->type == RED_OUT)
    {
		// printf(GREEN"1ok now u should open  this file > {%s} \n"RST, node->file_name);
        // if (open_infiles(node) < 0)
        //     return (ERROR);
    }
    else if (node->type == RED_IN)
    {
		printf(GREEN"2ok now u should open  this file  < {%s} \n"RST, node->file_name);
        // if (open_infiles(node, i) < 0)
        //     return (ERROR);
    }
    else if (node->type == APPEND)
    {
		printf(GREEN"3ok now u should open  this file >> {%s} \n"RST, node->file_name);
        // if (open_infiles(node, i) < 0)
        //     return (ERROR);
    }
	return (SUCCESS);
}
