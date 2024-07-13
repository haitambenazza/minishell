/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/13 14:35:27 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_env(char *s, t_shell *sh)
{
	t_env	*env;

	if (!ft_strlen(s))
		return (1);
	env = sh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, s))
			return (free(s), ft_strlen(env->value));
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

char	*ft_envirement(char *s, t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (!ft_strncmp(env->key, s))
			return (free(s), ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*get_env_var(char *s, int *i, t_shell *sh)
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
		return (NULL);
	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != ' ' && s[*i] != '$' \
		&& s[*i] != '\t' && s[*i] != '"')
	{
		env[len] = s[*i];
		len++;
		*i += 1;
	}
	return (ft_envirement(env, sh));
}

void	copy_from_env(t_shell *sh, char *str, int *j, int i, int *env_ind)
{
	char	*env;
	int		index;

	*env_ind += 1;
	index = 0;
	if (!sh->cmd[i][*env_ind])
	{
		str[*j] = '$';
		*j += 1;
		return ;
	}
	env = get_env_var(sh->cmd[i], env_ind, sh);
	if (!env)
		return ;
	while (env[index])
	{
		str[*j] = env[index];
		index++;
		*j += 1;
	}
	free(env);
}

void	expand_and_copy(t_shell *sh, int i, char *str)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (sh->cmd[i][j])
	{
		if (sh->cmd[i][j] == '\'')
		{
			str[len] = sh->cmd[i][j++];
			while (sh->cmd[i][j] && sh->cmd[i][j] != '\'')
				str[len++] = sh->cmd[i][j++];
			if (sh->cmd[i][j] == '\'')
				str[len++] = sh->cmd[i][j++];
		}
		if (sh->cmd[i][j] == '"')
		{
			while (sh->cmd[i][j] && sh->cmd[i][j] != '"' && sh->cmd[i][j] != '$')
				str[len++] = sh->cmd[i][j++];
			if (sh->cmd[i][j] == '$')
				copy_from_env(sh, str, &len, i, &j);
		}
		if (sh->cmd[i][j] == '$')
		{
				copy_from_env(sh, str, &len, i, &j);
		}
		else if(sh->cmd[i][j])
				str[len++] = sh->cmd[i][j++];
		if (!sh->cmd[i][j])
			break ;
	}
}

char	*new_cmd_expanded(t_shell *sh, int i)
{
	char	*str;
	int		len;

	len = len_new_cmd(sh->cmd[i], sh);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	expand_and_copy(sh, i, str);
	printf("%s\n", str);
	// free(sh->cmd[i]);
	return (str);
}

t_shell	*expander(t_shell *shell, t_token *t)
{
	t_shell	*tmp;
	int		i;

	if (!still_expandable(t, shell))
		return (NULL);
	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strchr(tmp->cmd[i], '$'))
			{
				new_cmd_expanded(tmp, i);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}
