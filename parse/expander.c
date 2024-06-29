/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/29 11:08:20 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_inside_quotes(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' || str[i])
			{
				i++;
				len++;
			}
			if (!str[i])
				return (len);
			i++;
		}
	}
	return (len);
}

int	quotes_range(char *str, char delimiter, char inside_char)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
		{
			i++;
			while (str[i] && str[i] != delimiter)
			{
				if (str[i] == inside_char)
					return (1);
				i++;
			}
		}
		if (!str[i])
			return (0);
		i++;
	}
	return (0);
}

int	get_len_env(t_shell *tmp, char *holder)
{
	t_env	*env_lst;

	env_lst = tmp->env;
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, holder))
			return (printf("len of $%zu\n", ft_strlen(env_lst->value)), ft_strlen(env_lst->value));
		env_lst = env_lst->next;
	}
	return (0);
}

int	get_env(t_shell *tmp, int index, int *i)
{
	char	*env;
	int		len;
	int		save_i;

	len = 0;
	*i += 1;
	save_i = *i;
	while (tmp->cmd[index][save_i] && tmp->cmd[index][save_i] != '"' &&\
		tmp->cmd[index][save_i] != '\'' /*&& tmp->cmd[index][*i] != '$'*/)
	{
		len++;
		save_i++;
	}
	env = malloc(sizeof(char) * (len + 1));
	env[len] = 0;
	len = 0;
	while (tmp->cmd[index][*i] && tmp->cmd[index][*i] != '"' &&\
		tmp->cmd[index][*i] != '\'' /*&& tmp->cmd[index][*i] != '$'*/)
	{
		env[len] = tmp->cmd[index][*i];
		len++;
		*i += 1;
	}
	printf("%s env\n", env);
	return (get_len_env(tmp, env));
}

int	fetch_len_env(t_shell *sh, int i_word)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while(sh->cmd[i_word][i])
	{
		if (sh->cmd[i_word][i] == '\'')
		{
			i++;
			len++;
			while (sh->cmd[i_word][i] && sh->cmd[i_word][i] != '\'')
			{
				i++;
				len++;
			}
		}
		else if (sh->cmd[i_word][i] == '$')
			len += get_env(sh, i_word, &i);
		else
			len++;
		if (!sh->cmd[i_word][i])
			return (len);
		i++;
	}
	return (len);
}

void	fetch_double_quotes(t_shell *cmds)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	while (cmds->cmd[i])
	{
		len = 0;
		j = 0;
		while (cmds->cmd[i][j])
		{
			if (cmds->cmd[i][j] == '$')
				len += fetch_len_env(cmds, i);
			else
				len++;
			j++;
		}
		i++;
	}
	printf("total len %d\n", len);
}

void	expander(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (shell->cmd[i])
		{
			if (ft_strchr(shell->cmd[i], '$'))
				fetch_double_quotes(tmp);
			i++;
		}
		tmp = tmp->next;
	}
}
