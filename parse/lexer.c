/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/21 16:38:38 by hbenazza         ###   ########.fr       */
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
	tokens[j] = 11;
	if (j == 0)
		return (free(tokens), NULL);
	return (tokens);
}

void	special_string(char *str)
{
	int	i;
	int	holder;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			holder = str[i];
			i++;
			while (str[i] && str[i] != holder)
			{
				if (str[i] == '|')
					str[i] = 1;
				else if (str[i] == ' ')
					str[i] = 2;
				i++;
			}
		}
		if (!str[i])
			break ;
		i++;
	}
}

t_shell	*lexer(char *inputs)
{
	t_shell	*shell;
	t_token	*t;
	char	*mask;

	mask = cmd_mask(inputs);
	if (!mask)
		return (NULL);
	t = tokenize(mask);
	if (!t)
		return (free(mask), NULL);
	parcing_pipe(t, mask);
	special_string(inputs);
	shell = create_list(inputs);
	if (!shell)
		return (free(t), free(mask), NULL);
	shell->mask = mask;
	shell->token = t;
	return (shell);
}
