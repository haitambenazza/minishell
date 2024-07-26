/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletenode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:25 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/26 10:32:33 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_node_env(t_env *envp)
{
	if (envp)
	{
		printf("freed   %p\n", envp);
		if (envp->key)
			free(envp->key);
		if (envp->value)
			free(envp->value);
		// envp->next = NULL;
		free(envp);
	}
}
