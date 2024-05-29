/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/29 17:00:43 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_pipes(t_shell *cmd)
{
	if (!cmd)
		return;
	cmd->next->input_fd = cmd->pipe[0];
	cmd->input_fd = cmd->pipe[1];
}

int	if_built_in_run(t_shell *tmp)
{
	if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "pwd"))
		return (ft_pwd(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "echo"))
		;//return (ft_echo(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "exit"))
		return (ft_exit(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "cd"))
		return (ft_cd(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "export"))
		return (ft_export(tmp));
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "env"))
		return (ft_env(tmp->env));
	return (1);
}

int	is_built_in(t_shell *tmp)
{
	if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "pwd"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "echo"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "exit"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "cd"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "export"))
		return (0);
	else if (tmp->cmd && !ft_strncmp(tmp->cmd[0], "env"))
		return (0);
	return (1);
}

void	*execute(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
	for (t_shell *t = cmds; t; t=t->next)
	{
		for (t_redirect *l = t->redirection; l; l=l->next)
		{
			printf("cmd   %s\n", t->cmd[0]);
			printf("redirection type of %u for file {%s}\n", l->type, l->file_name);
		}
	}
	if (tmp->next == NULL)
	{
		if (if_built_in_run(tmp))
			execute_cmd(tmp);
	}
	else
		open_pipes(tmp);
	if (!is_built_in(tmp) && tmp->next)
		execute_cmd(tmp->next);
	else if (is_built_in(tmp) && tmp->next)
		execute_cmd(tmp->next);
	clean_up(cmds);
	return (NULL);
}

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
			printf("%p in free\n", tmp->redirection);
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
	if (shell->mask)
		free(shell->mask);
	if (shell->token)
		free(shell->token);
	clean_redirect(shell);
	if (shell)
	{
		clean_lst(shell->env);
	}
	while (tmp)
	{
		if (tmp->cmd)
			free_array(tmp->cmd);
		tmp = tmp->next;
		free(shell);
		shell = tmp;
	}
}
