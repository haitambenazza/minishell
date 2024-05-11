/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/11 17:45:11 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser_error(void)
{
	write(2, "minishell: parsing error!\n", 26);
}

int	parcing_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < len_token(shell->mask))
	{
		printf("%d \n", shell->token[i]);
		i++;
	}
	if (shell->token[i] == PIPE)
		return (parser_error(), 1);
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
		if (parcing_tokens(shell))
			return (NULL);
		return (shell);
	}
	return (shell);
}
