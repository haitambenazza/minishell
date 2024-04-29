/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/29 17:20:28 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*create_list(int len)
{
	t_shell	*node;
	t_shell	*shell;
	int		i;

	i = 0;
	shell = ft_lstnew();
	while (i < len)
	{
		node = ft_lstnew();
		if (!node)
			return (NULL);
		ft_lstadd_back(&shell, node);
		i++;
	}
	return (shell);
}
t_shell	*lexer(char *inputs)
{
	t_shell	*shell;
	int		number;
	int		i;

	number = 0;
	i = 0;
	while (inputs[i])
	{
		if (inputs[i] == '|')
			number++;
		i++;
	}
	shell = create_list(number);
	if (!shell)
		return (NULL);
	return (shell);
}
