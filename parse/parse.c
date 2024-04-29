/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/29 18:09:48 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_command(t_shell *shell, char *input)
{
	t_shell	*tmp;
	char	**list;
	int		i;

	tmp = shell;
	list = ft_split(input, '|');
	if (!list)
		return (1);
	i = 0;
	while (tmp)
	{
		tmp->cmd = ft_split(list[i], ' ');
		if (!tmp->cmd)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

t_shell	*parsing(char *inputs)
{
	t_shell	*shell;

	shell = NULL;
	if (inputs)
	{
		shell = lexer(inputs);
		if (!shell)
			return (NULL);
		get_command(shell, inputs);
		return (shell);
	}
	return (shell);
}
