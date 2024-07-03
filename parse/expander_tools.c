/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:22:43 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/03 21:59:53 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	still_expandable(t_token *t)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (t[i] != 20)
	{
		if (t[i] == SINGEL_Q)
		{
			i++;
			while (t[i] != 20 && t[i] != SINGEL_Q)
				i++;
		}
		else if (t[i] == QUOTE)
		{
			i++;
			while (t[i] != 20 && t[i] != QUOTE)
			{
				if (t[i] == DOLLAR)
					c++;
				i++;
			}
		}
		else if (t[i] == DOLLAR)
			c++;
		i++;
	}
	return (c);
}
