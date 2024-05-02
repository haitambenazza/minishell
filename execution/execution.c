/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/02 15:45:51 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*taha(t_shell *cmds)
{
	//here you can work on execution fetch the commands with tmp->cmd[i]
	t_shell	*tmp;

	tmp = cmds;
	while (tmp)
	{
		printf("%s\n", tmp->cmd[0]);
		tmp = tmp->next;
	}
	return (NULL);
}
