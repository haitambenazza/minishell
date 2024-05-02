/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:17:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/02 15:08:43 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*ft_lstnew(char **cmd)
{
	t_shell	*node;

	node = (t_shell *)malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->next = NULL;
	return (node);
}
