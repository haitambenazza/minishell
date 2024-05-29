/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:01 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/29 08:18:34 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser_error()
{
	write(2, "minishell: parsing error!\n", 26);
}

int	find_next_command(t_token *token, int index)
{
	while (token[index] != 11)
	{
		index++;
		if (token[index] != ESPACE)
			break ;
	}
	if (token[index] == PIPE)
		return (1);
	return (0);
}

int	parsing_redirect(t_token *token, int index)
{
	int		c;
	t_token	t;
	t_token	opposite;

	c = 0;
	t = token[index];
	if (t == 4)
		opposite = 3;
	else
		opposite = 4;
	while (token[index] != 11)
	{
		index++;
		if (token[index] == t)
			c++;
		if (token[index] != ESPACE && token[index] != t)
			break ;
	}
	if (token[index] == PIPE || token[index] == 11 || c > 1 || token[index] == opposite)
		return (1);
	return (0);
}

int	parse_quote(t_token *token, int *i)
{
	t_token	t;

	t = token[*i];
	*i += 1;
	while (token[*i] != 11 && token[*i] != t)
		*i += 1;
	if (token[*i] == t)
		return (0);
	return (1);
}

int	parcing_pipe(t_token *token, char *mask)
{
	int		i;

	i = 0;
	(void)mask;
	if (token && token[i] == PIPE)// you need to create a file without content
		return (parser_error(), 1);
	while (token[i] != 11)
	{
		if ((token[i] == QUOTE || token[i] == SINGEL_Q) &&\
			parse_quote(token, &i))
			return (parser_error(), 1);
		if (token[i] == PIPE && find_next_command(token, i))
			return (parser_error(), 1);
		if ((token[i] == RED_IN || token[i] == RED_OUT) &&\
			parsing_redirect(token, i))
			return (parser_error(), 1);
		i++;
	}
	if (token[--i] == PIPE)
		return (parser_error(), 1);
	return (0);
}

t_redirect	*create_redirect_lst(char **cmd)
{
	t_redirect	*head;
	t_redirect	*node;
	int			i;

	i = 0;
	head = NULL;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], ">") || !ft_strncmp(cmd[i], "<"))
		{
			node = ft_lstnew_redirect(cmd[i], cmd[i + 1]);
			ft_lstadd_back3(&head, node);
		}
		else if (!ft_strncmp(cmd[i], "<<") || !ft_strncmp(cmd[i], ">>"))
		{
			node = ft_lstnew_redirect(cmd[i], cmd[i + 1]);
			ft_lstadd_back3(&head, node);
		}
		i++;
	}
	return (head);
}

void	redirections_lst(t_shell *shell)
{
	t_shell	*tmp;
	int		i;
	int		len;

	tmp = shell;
	while (tmp)
	{
		i = 0;
		len = 0;
		while (tmp->cmd[i])
		{
			if (!ft_strncmp(tmp->cmd[i], ">") || !ft_strncmp(tmp->cmd[i], "<"))
				len++;
			if (!ft_strncmp(tmp->cmd[i], "<<") || !ft_strncmp(tmp->cmd[i], ">>"))
				len++;
			if (len)
				tmp->redirection = create_redirect_lst(tmp->cmd);
			i++;
		}
		tmp = tmp->next;
	}
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
