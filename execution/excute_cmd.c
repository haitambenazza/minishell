/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:14:09 by tkoulal           #+#    #+#             */
/*   Updated: 2024/05/30 15:59:35 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_cmd(t_shell *cmds)
{
    // puts("execute");
    while (cmds)
    {
        cmds->pid = fork();
        if (!cmds->pid) //ana child
            execve("/bin/ls", cmds->cmd, cmds->envp);
        cmds = cmds->next;
    }
    while (wait(NULL) != -1);
    return (0);
}
