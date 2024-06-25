/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:15:04 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/25 11:01:30 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_quotes(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	i = 0;
	tmp = shell;
	while (tmp)
	{

		tmp = tmp->next;
	}
}
