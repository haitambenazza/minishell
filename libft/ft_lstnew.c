/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:17:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/13 13:48:54 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*ft_lstnew(char *str)
{
	t_shell	*node;

	// (void)str;
	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	if (str)
		node->cmd = ft_split(str, ' ');
	node->next = NULL;
	return (node);
}
