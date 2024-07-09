/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/08 17:11:36 by tkoulal          ###   ########.fr       */
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

int	is_in_range(char *str, char delimiter, char inside_char)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
		{
			i++;
			while (str[i] && str[i] != delimiter)
			{
				if (str[i] == inside_char)
					flag = 1;
				if (str[i] == inside_char && delimiter == '\'')
					flag = 0;
				i++;
			}
		}
		if (!str[i])
			return (0);
		i++;
	}
	return (flag);
}

int	len_env(char *s, t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, s))
			return (printf("%s vlau\n", env->value), free(s), ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

int	fetch_len_env(char *s, int *i, t_shell *sh)
{
	char	*env;
	int		len;
	int		save;

	len = 0;
	save = *i;
	while (s[save] && s[save] != '\'' && s[save] != ' ' && s[save] != '$' \
			&& s[save] != '\t' && s[save] != '"')
	{
		len++;
		save++;
	}
	env = malloc(sizeof(char) * (len + 1));
	env[len] = 0;
	if (!env)
		return (0);
	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != ' ' && s[*i] != '$' \
		&& s[*i] != '\t' && s[*i] != '"')
	{
		env[len] = s[*i];
		len++;
		*i += 1;
	}
	return (len_env(env, sh));
}

int	len_new_cmd(char *str, t_shell *sh)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			len++;
			while (str[i] && str[i] != '\'')
			{
				len++;
				i++;
			}
		}
		if (str[i] == '"')
		{
			i++;
			len++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					i++;
					len += fetch_len_env(str, &i, sh);
				}
				else
					len++;
				i++;
			}
		}
		if (str[i] == '$')
		{
			i++;
			len += fetch_len_env(str, &i, sh);
		}
		else
			len++;
		if (!str[i])
			break ;
		i++;
	}
	return (len);
}

char	*expand_and_copy(t_shell *sh, int i)
{
	char	*str;
	int		j;
	int		len;

	j = 0;
	len = len_new_cmd(sh->cmd[i], sh);
	printf("%d leeenn\n", len);
	str= malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (sh->cmd[i])
	{
		//start with single the double then dollar then normal
		i++;
	}
	return (str);
}

char	**new_cmd_expanded(t_shell *sh)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (lst_size(sh->cmd) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (sh->cmd[i])
	{
		if (ft_strchr(sh->cmd[i], '$'))
			arr[i] = expand_and_copy(sh, i);
		// else
		// 	arr[i] = copy_without_expand(sh, i);
		i++;
	}
	return ( arr);
}

t_shell	*expander(t_shell *shell, t_token *t)
{
	t_shell	*tmp;
	int		i;

	// printf("is true %d\n", still_expandable(t, shell));
	if (!still_expandable(t, shell))
		return (NULL);
	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (shell->cmd[i])
		{
			new_cmd_expanded(shell);
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}
