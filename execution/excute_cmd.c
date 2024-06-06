/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:14:09 by tkoulal           #+#    #+#             */
/*   Updated: 2024/06/06 14:06:58 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_cmd(t_shell *cmds)
{
    printf("should excute %s \n", cmds->cmd[0]);
    // while (cmds)
    // {
    //     cmds->pid = fork();
    //     if (!cmds->pid) //ana child
    //         execve("/bin/ls", cmds->cmd, cmds->envp);
    //     cmds = cmds->next;
    // }
    // while (wait(NULL) != -1);
    return (0);
}
