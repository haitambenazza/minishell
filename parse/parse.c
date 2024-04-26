/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/26 21:45:27 by hbenazza         ###   ########.fr       */
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
		if (cmd[i] != ' ' && cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<')
			mask[i] = 'c';
		else if (cmd[i] == ' ')
			mask[i] = 's';
		else if (cmd[i] == '|')
			mask[i] = 'p';
		else
			mask[i] = 'r';
		i++;
	}
	mask[i] = 0;
	return (mask);
}

// int	parce_mask(char *mask, t_shell *lst)
// {
// 	t_shell	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = lst;
// 	while (mask[i])
// 	{
// 		if (mask[i] == '2')
// 		{
// 			tmp->number_cmd++;
// 		}
// 	}
// }

int	parsing(char *inputs)
{
	t_shell	*lst;
	int		i;
	int		cmd;
	char	*lexer;

	i = 0;
	cmd = 0;
	lst = NULL;
	lexer = cmd_to_mask(inputs);
	if (!lexer)
		return (1);
	while (inputs[i])
	{
		if (inputs[i] == '|')
			cmd++;
		i++;
	}
	if (cmd)
		create_list(cmd, &lst);
	return (0);
}
