/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:14:09 by tkoulal           #+#    #+#             */
/*   Updated: 2024/06/07 22:30:16 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_cmd(t_shell *cmds)
{
    char *p = get_cmd(cmds->cmd[0], cmds->envp);
    cmds->pid = fork();
    if (cmds->pid == 0)
    {
        execve(p, cmds->cmd, cmds->envp);
        puts("Not found");
    }
    else
        while (waitpid(cmds->pid, NULL, WUNTRACED) == -1);
    free(p);
    return (0);
}
