/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/28 13:21:09 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_list(int count, t_shell **lst)
{
	t_shell	*node;
	int		i;

	i = 0;
	while (i < count)
	{
		node = ft_lstnew();
		if (!node)
			return (1);
		ft_lstadd_back(lst, node);
		i++;
	}
	return (0);
}

int	parsing(char *inputs)
{
	t_shell	*lst;
	int		i;
	int		cmd;

	i = 0;
	cmd = 0;
	lst = NULL;
	if (cmd)
		create_list(cmd, &lst);
	return (0);
}
