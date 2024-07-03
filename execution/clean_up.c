/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:02:17 by tkoulal           #+#    #+#             */
/*   Updated: 2024/07/02 11:41:37 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_array(char **v)
{
	int	i;

	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
	return (0);
}

void	clean_lst(t_env *shell)
{
	t_env	*lst;

	lst = shell;
	while (shell)
	{
		if (shell->key)
			free(shell->key);
		if (shell->value)
			free(shell->value);
		lst = shell->next;
		free(shell);
		shell = lst;
	}
}


void	clean_redirect(t_shell *shell)
{
	t_shell		*tmp;
	t_redirect	*redirect_tmp;

	tmp = shell;
	while (tmp)
	{
		while (tmp->redirection)
		{
			redirect_tmp = tmp->redirection->next;
			free(tmp->redirection->file_name);
			free(tmp->redirection);
			tmp->redirection = redirect_tmp;
		}
		tmp = tmp->next;
	}
}

void	clean_up(t_shell *shell)
{
	t_shell	*tmp;

	tmp = shell;
	clean_redirect(shell);
	while (tmp)
	{
		if (tmp->cmd)
			free_array(tmp->cmd);
		if (tmp)
			clean_lst(tmp->env);
		tmp = tmp->next;
		free(shell);
		shell = tmp;
	}
}
