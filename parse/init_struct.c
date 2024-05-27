/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:35:37 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/27 14:13:23 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*create_list(char *input)
{
	t_shell	*node;
	t_shell	*shell;
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(input, '|');
	shell = NULL;
	while (cmds[i])
	{
		node = ft_lstnew(cmds[i]);
		if (!node)
			return (NULL);
		ft_lstadd_back(&shell, node);
		i++;
	}
	free_array(cmds);
	return (shell);
}
