/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/14 11:44:59 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser_error(void)
{
	write(2, "minishell: parsing error!\n", 26);
}

int	find_next_command(t_token *token, int index)
{
	while (token[index] != 10)
	{
		index++;
		if (token[index] != ESPACE)
			break ;
	}
	if (token[index] == PIPE)
		return (1);
	return (0);
}

int	parcing_tokens(t_token *token, char *mask)
{
	int	i;

	i = 0;
	(void)mask;
	if (token)
	{
		if (token[i] == PIPE)
			return (parser_error(), 1);
		while (token[i] != 10)
		{
			if (token[i] == PIPE && find_next_command(token, i))
				return (parser_error(), 1);
			i++;
		}
		if (token[--i] == PIPE)
			return (parser_error(), 1);
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
		free(inputs);
		if (!shell)
			return (NULL);
	}
	else
		free(inputs);
	return (shell);
}
