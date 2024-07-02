/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/01 12:30:37 by hbenazza         ###   ########.fr       */
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
	printf("holder %s\n", holder);
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, holder))
			return (free(holder), ft_strlen(env_lst->value));
		env_lst = env_lst->next;
	}
	free(holder);
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
		tmp->cmd[index][save_i] != '\'' && tmp->cmd[index][save_i] != '$')
	{
		len++;
		save_i++;
	}
	env = malloc(sizeof(char) * (len + 1));
	env[len] = 0;
	len = 0;
	while (tmp->cmd[index][*i] && tmp->cmd[index][*i] != '"' &&\
		tmp->cmd[index][*i] != '\'' && tmp->cmd[index][*i] != '$')
	{
		env[len] = tmp->cmd[index][*i];
		len++;
		*i += 1;
	}
	printf("*--------------------*\n");
	return (get_len_env(tmp, env));
}

int	fetch_len_env(t_shell *sh, int i_word, int *j)
{
	int		len;

	len = 0;
	while(sh->cmd[i_word][*j])
	{
		if (sh->cmd[i_word][*j] == '$')
			len += get_env(sh, i_word, j);
		else
			len++;
		if (!sh->cmd[i_word][*j])
			return (len);
		*j += 1;
	}
	return (len);
}

int	non_expanding_len(t_shell *sh, int *j, int i)
{
	int	len;

	len = 1;
	*j += 1;
	while (sh->cmd[i][*j] && sh->cmd[i][*j] != '\'')
	{
		*j += 1;
		len++;
	}
	if (sh->cmd[i][*j] == '\'')
		len++;
	return (len);
}
char	*get_env_from_lst(t_shell *tmp, char *holder)
{
	t_env	*env_lst;

	env_lst = tmp->env;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, holder))
			return (free(holder), env_lst->value);
		env_lst = env_lst->next;
	}
	free(holder);
	return (NULL);
}

char	*get_env_value(t_shell *tmp, int index, int *i)
{
	char	*env;
	int		len;
	int		save_i;

	len = 0;
	*i += 1;
	save_i = *i;
	while (tmp->cmd[index][save_i] && tmp->cmd[index][save_i] != '"' &&\
		tmp->cmd[index][save_i] != '\'' && tmp->cmd[index][*i] != '$')
	{
		len++;
		save_i++;
	}
	env = malloc(sizeof(char) * (len + 1));
	env[len] = 0;
	len = 0;
	while (tmp->cmd[index][*i] && tmp->cmd[index][*i] != '"' &&\
		tmp->cmd[index][*i] != '\'' && tmp->cmd[index][*i] != '$')
	{
		env[len] = tmp->cmd[index][*i];
		len++;
		*i += 1;
	}
	return (get_env_from_lst(tmp, env));
}
char	*replace_with_env(t_shell *sh, int len, int i)
{
	char	*str;
	char	*env;
	int		j;
	int		index_env;

	j = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	len = 0;
	while (sh->cmd[i][j])
	{
		if (sh->cmd[i][j] == '\'')
		{
			str[len] = sh->cmd[i][j];
			len++;
			j++;
			while (sh->cmd[i][j] && sh->cmd[i][j] != '\'')
			{
				str[len] = sh->cmd[i][j];
				len++;
				j++;
			}
		}
		else if (sh->cmd[i][j] == '$')
		{
			env = get_env_value(sh, i, &j);
			index_env = 0;
			while (env[index_env])
			{
				str[len] = env[index_env];
				len++;
				index_env++;
			}
		}
		else
		{
			str[len] = sh->cmd[i][j];
			j++;
			len++;
		}
	}
	printf("%s final \n", str);
	return (str);
}

char	*fetch_double_quotes(t_shell *cmds, int i)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (cmds->cmd[i][j])
	{
		if (cmds->cmd[i][j] == '$')
			len += fetch_len_env(cmds, i, &j);
		else if (cmds->cmd[i][j] == '\'')
			len += non_expanding_len(cmds, &j, i);
		else
			len++;
		if (!cmds->cmd[i][j])
			break ;
		j++;
	}
	replace_with_env(cmds, len, i);
	return (NULL);
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
				fetch_double_quotes(tmp, i);
			i++;
		}
		tmp = tmp->next;
	}
}
