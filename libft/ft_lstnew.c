/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:17:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/25 10:04:57 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*ft_lstnew()
{
	t_shell	*node;

	node = (t_shell *)malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}
