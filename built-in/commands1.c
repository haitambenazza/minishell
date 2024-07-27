/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:37:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/27 20:06:14 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((i == 0) && str[i] != '-')
			return (1);
		if (i >= 1 && str[i] != 'n')
			return (1);
		i++;
	}
	return (SUCCESS);
}

int	run_option(t_shell *sh)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	if (check_option(sh->cmd[i]))
		return (0);
	while (sh->cmd[i])
	{
		j = i;
		if (check_option(sh->cmd[i]))
			flag = 1;
		if (flag && sh->cmd[++j])
			printf("%s ", sh->cmd[i]);
		else if (flag)
			printf("%s", sh->cmd[i]);
		i++;
	}
	return (1);
}

int		ft_echo(t_shell *sh)
{
	int	i;

	i = 1;
	if (!ft_strlen(sh->cmd[1]))
		printf("\n");
	if (run_option(sh))
		return (1);
	else
	{
		while (sh->cmd[i])
		{
			printf("%s ", sh->cmd[i]);
			i++;
		}
		printf("\n");
	}
	return (0);
}

int	ft_pwd(t_shell *shell)
{
	char	*dir;

	(void)shell;
	dir = getcwd((void *)0, 0);
	if (dir)
		printf("%s\n", dir);
	else
	{
		exit_status = 30;
		return (perror("pwd"), exit_status);
	}
	free(dir);
	exit_status = 0;
	return (exit_status);
}

void	set_current_dir(t_shell *sh)
{
	t_env	*tmp;
	char	*pwd;

	tmp = sh->env;
	pwd = getcwd(NULL, 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	tmp = sh->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
}

void	get_old_dir(t_shell *sh, char *oldpwd)
{
	t_env	*tmp;

	tmp = sh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	tmp = sh->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	free(oldpwd);
}

int	ft_cd(t_shell *shell)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (lst_size(shell->cmd) > 2)
	{
		exit_status = 1;
		return (printf("cd cannot take more than one argument!\n"), exit_status);
	}
	if (!shell->cmd[1])
	{
		if (chdir(getenv("HOME")))
			return (perror("cd"), exit_status = 1, 1);
		get_old_dir(shell, old_pwd);
		set_current_dir(shell);
	}
	else
	{
		if (chdir(shell->cmd[1]))
			return (perror("cd"), exit_status = 1, 1);
		get_old_dir(shell, old_pwd);
		set_current_dir(shell);
	}
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
				ft_lstadd_back_env(&sh->env_copy, ft_lstnew_env(tmp->cmd[i]));
		}
		else if (!is_in_env(tmp, tmp->cmd[i], 0))
			ft_lstadd_back_env(&sh->env_copy, ft_lstnew_env(tmp->cmd[i]));
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
	i = 1;
	while (sh->cmd[i])
	{
		if (is_in_env(sh, sh->cmd[i], 0))
			remove_from_export(sh, sh->cmd[i]);
		if (is_in_env(sh, sh->cmd[i], 1))
			remove_from_env(sh, sh->cmd[i]);
		i++;
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	clean_up(shell, 1);
	write(1, "exit\n", 5);
	exit(exit_status);
}
