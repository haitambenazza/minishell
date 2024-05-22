/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:38 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/22 18:59:55 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_env(char **env, int len)
{
	t_env	*lst;
	int		i;

	lst = malloc((t_env) * (len + 1));
	if (!lst)
		return (NULL);
	i = 0;
	while (env[i])
	{
		lst = ft_lstnew(env[i]);
		if (!lst)
			return (NULL);
		ft_lstadd_back2(env, lst);
		i++;
	}
	return (env);
}

int	main(int c, char **v, char **env)
{
	(void)v;
	if (c == 1)
	{
		t_env	*env_lst;
		
		int	len;

		len = 0;
		if (!ft_strlen(env[0]))
			return (printf("no env found exiting minishell...\n"), 1);
		while (env[len])
			len++;
		env_lst = new_env(env, len);
		if (reading_promp())
			return (1);
	}
	else
	{
		printf("cant take arguments!\n");
		return (1);
	}
	return (0);
}

