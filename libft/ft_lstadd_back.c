/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:20:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/24 18:53:20 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	t_shell	*traverse;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	traverse = *lst;
	while (traverse->next)
	{
		traverse = traverse->next;
	}
	traverse->next = new;
}
