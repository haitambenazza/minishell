/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:19:09 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/21 18:28:48 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
}

void	expand(t_shell *lst)
{
	t_shell	*tmp;
	int		i;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		
		tmp = tmp->next;
	}
}
