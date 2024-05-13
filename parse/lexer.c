/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/13 15:53:46 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//AST here
//dont forgot to expand the env variables $var in the env variables
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

t_token	*tokenize(char *m)
{
	t_token	*tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(t_token) * (len_token(m) + 1));
	if (!tokens)
		return (NULL);
	while (m[i])
	{
		//convert the mask to tokens
		while ((m[i] == '1' || m[i] == '0') && (m[i] == m[i + 1]))
			i++;
		cmd_tokens(m[i], tokens, j);
		j++;
		i++;
	}
	return (tokens);
}

t_shell	*lexer(char *inputs)
{
	t_shell	*shell;
	t_token	*t;
	char	*mask;
	int		number;
	int		i;

	number = 0;
	i = 0;
	mask = cmd_mask(inputs);
	if (!mask)
		return (NULL);
	t = tokenize(mask);
	if (!t)
		return (NULL);
	while (i < len_token(mask))
	{
		if (t[i] == PIPE)
			number++;
		i++;
	}
	shell = create_list(inputs);
	if (!shell)
		return (free(mask), NULL);
	shell->token = t;
	shell->mask = mask;
	return (shell);
}
