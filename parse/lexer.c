/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:34:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/06 21:22:14 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//AST here
//dont forgot to expand the env variables $var in the env variables

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
void	copy_char(char *out, char *str, int *len, int *i)
{
	out[*len] = str[*i];
	*i += 1;
	*len += 1;
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
int	lst_size(char **lst)
{
	int	len;

	len = 0;
	while (lst[len])
		len++;
	return (len);
}

char	*new_cmd(char *str, t_shell *shell)
{
	char	*output;
	char	**lst;
	int		i;

	(void)shell;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			lst = ft_split(str, '\'');
			output = ft_strjoin2(lst_size(lst), lst, "");
			return (free(str), free_array(lst), output);
		}
		else if (str[i] == '"')
		{
			lst = ft_split(str, '"');
			output = ft_strjoin2(lst_size(lst), lst, "");
			return (free(str), free_array(lst), output);
		}
		i++;
	}
	return (str);
}

void	remove_quotes(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			tmp->cmd[i] = new_cmd(tmp->cmd[i], tmp);
			i++;
		}
		tmp = tmp->next;
	}

}
int	len_cmd(t_shell *shell)
{
	t_shell	*t;
	int		len;
	int		i;

	len = 0;
	i = 0;
	t = shell;
	while (t->cmd[i])
	{
		if (!ft_strncmp(t->cmd[i], ">") || !ft_strncmp(t->cmd[i], ">>"))
			i++;
		else if (!ft_strncmp(t->cmd[i], "<") || !ft_strncmp(t->cmd[i], "<<"))
			i++;
		else
			len++;
		i++;
	}
	return (len);
}
void	ft_malloc(char *str, char **arr, int *len)
{
	int	i;

	arr[*len] = malloc((ft_strlen(str) + 1));
	if (!arr[*len])
		return ;
	i = 0;
	while (str[i])
	{
		arr[*len][i] = str[i];
		i++;
	}
	arr[*len][i] = 0;
	*len += 1;
}

void	only_cmd(t_shell *shell)
{
	t_shell	*tmp;
	char	**arr;
	int		i;
	int		len;

	tmp = shell;
	while (tmp)
	{
		i = 0;
		len = len_cmd(tmp);
		arr = malloc(sizeof(char*) * (len + 1));
		arr[len] = 0;
		len = 0;
		if (!arr)
			return ;
		while (tmp->cmd[i])
		{
			if (!ft_strncmp(tmp->cmd[i], ">") || !ft_strncmp(tmp->cmd[i], ">>"))
				i++;
			else if (!ft_strncmp(tmp->cmd[i], "<") || !ft_strncmp(tmp->cmd[i], "<<"))
				i++;
			else
				ft_malloc(tmp->cmd[i], arr, &len);
			i++;
		}
		free_array(tmp->cmd);
		tmp->cmd = arr;
		tmp = tmp->next;
	}
}
void	count_quotes(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	i = 0;
	tmp = shell;
	while (tmp)
	{

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
	special_string(sp);
	shell = create_list(sp);
	if (!shell)
		return (free(sp), free(t), free(mask), NULL);
	count_quotes(shell);
	remove_quotes(shell);
	redirections_lst(shell);
	only_cmd(shell);
	return (free(sp), free(t), free(mask), shell);
}
