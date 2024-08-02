/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:47:39 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/31 22:41:12 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char*	generate_name(int i)
{
	char *path;
    int j = 0;

	path = ttyname(0);
	while (path[j])
    {
		path[j] += i + 1;
        j++;
    }
    return(ft_strdup(path));
}

int    free_if_there_is_a_del(int *flag, char *line, t_redirect *red_tmp)
{
    (void)flag;
    if (!ft_strncmp(line, red_tmp->file_name))
    {
        free(line);
        return (0);
    }
    return (1);
}

int len_of_env(char *line)
{
    int len = 0;
    int i = 0;

    while (line[i] && line[i] != '$')
        i++;
    if (line[i] == '$')
        i++;
    while (line[i] && line[i] != '\'' && line[i] != ' ' && line[i] != '"' && line[i] != '\t' && line[i] != '$')
    {
        i++;
        len++;
    }
    return (len);
}

char *get_env_to_line(char *new, char *line)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (line[i] && line[i] != '$')
        i++;
    if (line[i] == '$')
        i++;
    while (line[i] && line[i] != '\'' && line[i] != ' ' && line[i] != '"' && line[i] != '\t' && line[i] != '$')
    {
        new[len] = line[i];
        i++;
        len++;
    }
    return(getenv(new));
}