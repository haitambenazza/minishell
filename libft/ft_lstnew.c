/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:17:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/21 10:28:45 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	string_special(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == 1)
				cmd[i][j] = '|';
			else if (cmd[i][j] == 2)
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
}

t_shell	*ft_lstnew(char *str)
{
	t_shell	*node;

	// (void)str;
	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	if (str)
		node->cmd = ft_split(str, ' ');
	string_special(node->cmd);
	node->next = NULL;
	return (node);
}
