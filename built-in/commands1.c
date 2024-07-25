/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:37:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/25 22:36:21 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*dir;
	int		i;

	i = 0;
	while (shell->cmd[i])
		i++;
	if (i > 1)
		return (write(2, "pwd: too many arguments! \n", 26), 1);
	dir = getcwd((void *)0, 0);
	if (dir)
		printf("%s\n", dir);
	else
		return (perror("pwd"), 1);
	free(dir);
	return (0);
}

int	ft_cd(t_shell *shell)
{
	char	*home_path;
	char	*args;

	args = NULL;
	if (shell->cmd)
		args = ft_strjoin2(lst_size(shell->cmd + 1), shell->cmd + 1, "");
	if (!ft_strncmp(args, "~") || lst_size(shell->cmd) == 1)
	{
		home_path= getenv("HOME");
		if (chdir(home_path))
			return (perror("cd"), 2);
	}
	else if (chdir(args))
		return (perror("cd"), 2);
	return (0);
}

int	is_in_env(t_shell *sh, char *var_env, int flag)
{
	t_env	*tmp;
	t_env	*tmpcp;

	tmp = sh->env;
	tmpcp = sh->env_copy;
	while (tmp && flag)
	{
		if (!ft_strncmp_env(tmp->key, var_env))
			return (1);
		tmp = tmp->next;
	}
	while (tmpcp && !flag)
	{
		if (!ft_strncmp_env(tmpcp->key, var_env))
			return (1);
		tmpcp = tmpcp->next;
	}
	return (0);
}

int	export_to_env(t_shell *sh)
{
	t_shell	*tmp;
	int		i;
	int		j;

	tmp = sh;
	i = 1;
	while (tmp->cmd[i])
	{
		j = 0;
		while (tmp->cmd[i][j] && (tmp->cmd[i][j] == ' ' || tmp->cmd[i][j] == '\t'))
			j++;
		if (tmp->cmd[i][j] == '=')
			return (exit_status = 13, printf("bad assignemet\n"), exit_status);
		if (ft_strchr(tmp->cmd[i], '=') && !is_in_env(tmp, tmp->cmd[i], 1))
		{
			ft_lstadd_back_env(&tmp->env, ft_lstnew_env(tmp->cmd[i]));
			if (!is_in_env(tmp, tmp->cmd[i], 0))
				ft_lstadd_back_env(&tmp->env_copy, ft_lstnew_env(tmp->cmd[i]));
		}
		else if (!is_in_env(tmp, tmp->cmd[i], 0))
			ft_lstadd_back_env(&tmp->env_copy, ft_lstnew_env(tmp->cmd[i]));
		i++;
	}
	exit_status = 0;
	return (exit_status);
}

int	ft_export(t_shell *shell)
{
	t_env	*tmp;
	t_env	*envp;

	tmp = shell->env;
	envp = shell->env_copy;
	if (lst_size(shell->cmd) == 1)
	{
		while (envp)
		{
			printf("declare -x %s=%s\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
	else
		export_to_env(shell);
	exit_status = 0;
	return (exit_status);
}

int	ft_env(t_env *shell)
{
	t_env	*tmp;

	tmp = shell;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	remove_from_env(t_shell *sh, char *target)
{
	t_env	*tmp;
	t_env	*traverse;
	t_env	*save_next;

	traverse = sh->env;
	while (traverse)
	{
		tmp = traverse->next;
		if (tmp && !ft_strncmp(tmp->key, target))
		{
			save_next = tmp->next;
			delete_node_env(tmp);
			traverse->next = save_next;
		}
		traverse = traverse->next;
	}
}

void	remove_from_export(t_shell *sh, char *target)
{
	t_env	*tmp;
	t_env	*traverse;
	t_env	*save_next;

	traverse = sh->env_copy;
	while (traverse)
	{
		tmp = traverse->next;
		if (tmp && !ft_strncmp(tmp->key, target))
		{
			save_next = tmp->next;
			delete_node_env(tmp);
			traverse->next = save_next;
		}
		traverse = traverse->next;
	}
}

int	ft_unset(t_shell *sh)
{
	t_env	*envp;
	t_env	*envp_cp;
	int		i;

	envp = sh->env;
	envp_cp = sh->env_copy;
	i = 0;
	while (sh->cmd[++i])
	{
		if (is_in_env(sh, sh->cmd[i], 0))
		{
			remove_from_export(sh, sh->cmd[i]);
			remove_from_env(sh, sh->cmd[i]);
		}
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	clean_up(shell);
	write(1, "exit\n", 5);
	exit(exit_status);
}
