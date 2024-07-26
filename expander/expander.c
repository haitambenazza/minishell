/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/26 20:54:06 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	copy_in_single_quotes(char *s, int *j, t_shell *sh, int i, int *len)
{
	s[*len] = sh->cmd[i][*j];
	*len += 1;
	*j += 1;
	while (sh->cmd[i][*j] && sh->cmd[i][*j] != '\'')
	{
		s[*len] = sh->cmd[i][*j];
		*len += 1;
		*j += 1;
	}
	if (sh->cmd[i][*j] == '\'')
	{
		s[*len] = sh->cmd[i][*j];
		*len += 1;
		*j += 1;
	}
}

void	expand_and_copy(t_shell *s, int i, char *str)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (s->cmd[i][j])
	{
		if (s->cmd[i][j] == '\'')
			copy_in_single_quotes(str, &j, s, i, &len);
		if (s->cmd[i][j] == '"')
		{
			while (s->cmd[i][j] && s->cmd[i][j] != '"' && s->cmd[i][j] != '$')
				str[len++] = s->cmd[i][j++];
			if (s->cmd[i][j] == '$')
				copy_from_env(s, str, &len, i, &j);
		}
		if (s->cmd[i][j] == '$')
				copy_from_env(s, str, &len, i, &j);
		else if(s->cmd[i][j])
				str[len++] = s->cmd[i][j++];
	}
}

char	*new_cmd_expanded(t_shell *sh, int i)
{
	char	*str;
	int		len;

	len = len_new_cmd(sh->cmd[i], sh);
	// printf("%d len of exp\n", len);
	str = ft_calloc(sizeof(char) , (len + 1));
	str[len] = 0;
	expand_and_copy(sh, i, str);
	free(sh->cmd[i]);
	return (str);
}

t_shell	*expander(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	if (!still_expandable(shell))
		return (NULL);
	tmp = shell;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strchr(tmp->cmd[i], '$'))
				tmp->cmd[i] = new_cmd_expanded(tmp, i);
			i++;
		}
		tmp = tmp->next;
	}
	return (expander(shell));
}
