/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_promp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:52 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/29 11:22:04 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	history(char *str)
{
	if (!str)
		return (1);
	if (ft_strlen(str))
		add_history(str);
	return (0);

}

t_env	*create_lst_env(char **env)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		node = ft_lstnew2(env[i]);
		ft_lstadd_back2(&head, node);
		i++;
		node = node->next;
	}
	return (head);
}

void	init_env_lst(t_shell *sh, char **env)
{
	t_shell	*tmp;

	tmp = sh;
	while (tmp)
	{
		tmp->env = create_lst_env(env);
		tmp = tmp->next;
	}
}

int	reading_promp(char **env)
{
	t_shell	*shell;
	char	*inputs;
	int		err;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_empty);
	err = 0;
	while (1337)
	{
		inputs = readline("minishell~> ");
		if (!inputs)
			return (cntl_D(), 0);
		shell = parsing(ft_strtrim(inputs, " "));
		if (shell)
			init_env_lst(shell, env);
		if (history(inputs))
			return (free(inputs), 1);
		free(inputs);
		for (t_shell *tmp = shell; tmp; tmp=tmp->next)
		{
			for (int i = 0; tmp->cmd[i]; i++)
				printf("%s\n", tmp->cmd[i]);
		}
		// if (shell)
		// {
		// 	for (t_env *env = shell->env; env; env=env->next)
		// 	{
		// 		printf("%s=%s\n", env->key, env->value);
		// 	}
		// }
		clean_up(shell);
		// if (shell)
		// 	err = run_execution(shell);
		// if (err < 0)
		// 	return (1);
	}
	return (0);
}
