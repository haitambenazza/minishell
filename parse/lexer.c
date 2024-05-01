/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/01 18:41:31 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//AST here

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

void	masking(char *str, int i, char c)
{
	//the rest of the mask from cmd_mask
	if (c == '>')
		str[i] = '4';
	else if (c == '<')
		str[i] = '3';
	else if (c == ' ')
		str[i] = '1';
	else
		str[i] = '0';
}

char	*cmd_mask(char *str)
{
	char	*mask;
	int		i;

	i = 0;
	mask = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!mask)
		return (NULL);
	while (str[i])
	{
		//convert inputs to masks
		if (str[i] == '\'')
			mask[i] = '6';
		else if (str[i] == '"')
			mask[i] = '5';
		else if (str[i] == '|')
			mask[i] = '2';
		else if (str[i] == '&')
			mask[i] = '8';
		else
			masking(mask, i, str[i]);
		i++;
	}
	mask[i] = 0;
	return (mask);
}

int	len_token(char *m)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (m[i])
	{
		//calculate the lenght of the tokens according to the mask
		if ((m[i] == '0' || m[i] == '1') && m[i] != m[i + 1])
			len++;
		if ((m[i] != '0' && m[i] != '1'))
			len++;
		i++;
	}
	return (len);
}

void	cmd_tokens(char mask, t_token *t, int i)
{
	if (mask == '2')
		t[i] = PIPE;
	else if (mask == '3')
		t[i] = REDIRECTION_IN;
	else if (mask == '4')
		t[i] = REDIRECTION_OUT;
	else if (mask == '5')
		t[i] = QUOTE;
	else if (mask == '6')
		t[i] = SINGEL_Q;
	else if (mask == '8')
		t[i] = AND;
	else if (mask == '1')
		t[i] = ESPACE;
	else
		t[i] = CMD;
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
