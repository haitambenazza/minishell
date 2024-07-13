/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:22:43 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/13 13:33:15 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token(t_token *t, int i, int c)
{
	while (t[i] != 20)
	{
		if (t[i] == SINGEL_Q)
		{
			i += 1;
			while (t[i] != 20 && t[i] != SINGEL_Q)
				i += 1;
		}
		else if (t[i] == QUOTE)
		{
			i += 1;
			while (t[i] != 20 && t[i] != QUOTE)
			{
				if (t[i] == DOLLAR)
					c += 1;
				i += 1;
			}
		}
		else if (t[i] == DOLLAR)
			c += 1;
		i += 1;
	}
	return (c);
}

int	still_expandable(t_token *t, t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->cmd[i])
	{
		if (i > 0 && !ft_strncmp(sh->cmd[i - 1], "<<") && check_token(t, 0, 0))
			return (1);
		else if (!i && check_token(t, 0, 0))
			return (1);
		i++;
	}
	return (0);
}
