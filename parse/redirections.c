/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:19:24 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/25 19:03:56 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirect	*create_redirect_lst(char **cmd, int *i)
{
	t_redirect	*head;
	t_redirect	*node;

	head = NULL;
	while (cmd[*i])
	{
		if (!ft_strncmp(cmd[*i], ">") || !ft_strncmp(cmd[*i], "<"))
		{
			node = ft_lstnew_redirect(cmd[*i], cmd[*i + 1]);
			ft_lstadd_back_redirect(&head, node);
		}
		if (!ft_strncmp(cmd[*i], "<<") || !ft_strncmp(cmd[*i], ">>"))
		{
			node = ft_lstnew_redirect(cmd[*i], cmd[*i + 1]);
			ft_lstadd_back_redirect(&head, node);
		}
		*i += 1;
	}
	return (head);
}

void	redirections_lst(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	tmp = shell;

	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (!ft_strncmp(tmp->cmd[i], ">") || !ft_strncmp(tmp->cmd[i], "<"))
				tmp->redirection = create_redirect_lst(tmp->cmd, &i);
			if (!ft_strncmp(tmp->cmd[i], "<<") || !ft_strncmp(tmp->cmd[i], ">>"))
				tmp->redirection = create_redirect_lst(tmp->cmd, &i);
			if (!tmp->cmd[i])
				break ;
			i++;
		}
		tmp = tmp->next;
	}
}
