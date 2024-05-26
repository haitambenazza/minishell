/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/26 12:01:24 by hbenazza         ###   ########.fr       */
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

int	new_lenght(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i] != str[i + 1])
			len += 2;
		i++;
	}
	return (len);
}

void	skip_quotes(char *out, int *len, char *str, int *i)
{
	char	quote;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[*i];
		out[*len] = str[*i];
		*len += 1;
		*i += 1;
		while (str[*i] && str[*i] != quote)
		{
			out[*len] = str[*i];
			*len += 1;
			*i += 1;
		}
		if (str[*i] == '"' || str[*i] == '\'')
		{
			out[*len] = str[*i];
			*i += 1;
			*len += 1;
		}
	}
}
void	spacing(char *out, char *str, int *len, int *i)
{
	if ((str[*i] == '>' || str[*i] == '<') && str[*i] != str[*i - 1])
	{
		out[*len] = ' ';
		*len += 1;
	}
	if (*i && (str[*i - 1] == '>' || str[*i - 1] == '<') && str[*i] != str[*i - 1])
	{
		out[*len] = ' ';
		*len += 1;
	}
}

char	*add_space(char *str)
{
	char	*out;
	int		i;
	int		len;

	len = new_lenght(str);
	out = malloc(sizeof(char) * (len + 1));
	printf("%s %d\n", str, len);
	if (!out)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		skip_quotes(out, &len, str, &i);
		spacing(out, str, &len, &i);
		out[len] = str[i];
		len++;
		i++;
	}
	out[len] = 0;
	return (out);
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
	if (parcing_pipe(t, mask))
		return (NULL);
	char *sp = add_space(inputs);
	special_string(sp);
	shell = create_list(sp);
	if (!shell)
		return (free(t), free(mask), NULL);
	for (t_shell *tmp = shell; tmp; tmp=tmp->next)
	{
		for (int i = 0; tmp->cmd[i]; i++)
			printf("%s\n", tmp->cmd[i]);
	}
	shell->mask = mask;
	shell->token = t;
	return (shell);
}
