/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:12:25 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/08 17:21:59 by tkoulal          ###   ########.fr       */
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