/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/29 11:23:55 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//change the value of pipes and space to save them later
void	change_value_others(char *str, int holder)
{
	(void)holder;
	if (*str == '>')
		*str = 3;
	else if (*str == '<')
		*str = 4;
	// else if
}

void	change_value_inside_quotes(char *str)
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
				else
					change_value_others(&str[i], holder);
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
		if (*i && (str[*i - 1] == '>' || str[*i - 1] == '<'))
		{
			out[*len] = ' ';
			*len += 1;
		}
		quote = str[*i];
		out[*len] = str[*i];
		*len += 1;
		*i += 1;
		while (str[*i] && str[*i] != quote)
			copy_char(out, str, len, i);
		if (str[*i] == '"' || str[*i] == '\'')
			copy_char(out, str, len, i);
	}
}
void	spacing(char *out, char *str, int *len, int *i)
{
	if (*i && (str[*i] == '>' || str[*i] == '<') && str[*i] != str[*i - 1])
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
	if (!out)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		skip_quotes(out, &len, str, &i);
		spacing(out, str, &len, &i);
		out[len] = str[i];
		if (!str[i])
			break ;
		len++;
		i++;
	}
	out[len] = 0;
	return (out);
}

void	only_cmd(t_shell *shell)
{
	t_shell	*tmp;

	tmp = shell;
	while (tmp)
	{
		split_cmd(tmp);
		tmp = tmp->next;
	}
}

t_shell	*lexer(char *inputs)
{
	t_shell	*shell;
	t_token	*t;
	char	*sp;
	char	*mask;

	mask = cmd_mask(inputs);
	if (!mask)
		return (NULL);
	t = tokenize(mask);
	if (!t)
		return (free(mask), NULL);
	if (parcing_pipe(t, mask))
		return (free(t), free(mask), NULL);
	sp = add_space(inputs);
	change_value_inside_quotes(sp);
	shell = create_list(sp);
	if (!shell)
		return (free(sp), free(t), free(mask), NULL);
	// expander(shell);
	only_cmd(shell);
	remove_quotes(shell);
	redirections_lst(shell);
	return (free(sp), free(t), free(mask), shell);
}
