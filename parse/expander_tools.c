/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:22:43 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/17 23:38:06 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expand_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == '$')
					return (1);
			}
		}
		else if (str[i] == '$')
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_expandable_var(t_shell *sh)
{
	t_shell	*tmp;
	int		i;

	tmp = sh;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (is_expand_valid(tmp->cmd[i]))
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	still_expandable(t_shell *sh)
{
	int	i;

	i = 0;
	if (check_expandable_var(sh))
		return (1);
	while (sh->cmd[i])
	{
		if (i && !ft_strncmp(sh->cmd[i - 1], ">>") &&\
			!ft_strncmp(sh->cmd[i], "$"))
			return (1);
		i++;
	}
	return (0);
}
