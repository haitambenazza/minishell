/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/25 21:07:21 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_list(int count, char **cmd, t_shell **lst)
{
	t_shell	*node;
	int		i;

	i = 0;
	(void)cmd;
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

char	*cmd_to_mask(char *cmd)
{
	char	*mask;
	int		i;

	i = 0;
	mask = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!mask || !cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '|')
			mask[i] = '0';
		else if (cmd[i] == ' ')
			mask[i] = '1';
		else
			mask[i] = '2';
		i++;
	}
	mask[i] = 0;
	return (mask);
}

int	parsing(char *inputs)
{
	t_shell	*lst;
	int		i;
	int		cmd;

	i = 0;
	cmd = 0;
	lst = NULL;
	if (!cmd_to_mask(inputs))
		return (1);
	while (inputs[i])
	{
		if (inputs[i] == '|')
			cmd++;
		i++;
	}
	if (cmd)
		create_list(cmd, ft_split(inputs, '|'), &lst);
	return (0);
}
