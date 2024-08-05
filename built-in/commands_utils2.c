/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:06:43 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/05 21:32:52 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	change_value_export(t_env *env, char *key)
{
	char	*value;
	int		i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strnncmp(key, env->key, i))
		{
			value = env->value;
			env->value = ft_strdup(key + i + 1);
			free(value);
		}
		env = env->next;
	}
}

void	change_value_env(t_shell *n, char *key)
{
	int		i;
	t_env	*env;
	char	*value;

	i = 0;
	env = n->env;
	while (key[i] && key[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strnncmp(key, env->key, i))
		{
			value = env->value;
			env->value = ft_strdup(key + i + 1);
			free(value);
		}
		env = env->next;
	}
	change_value_export(n->env_copy, key);
	g_exit_status = 0;
}
