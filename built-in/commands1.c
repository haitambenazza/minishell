/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:37:57 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/11 16:49:50 by hbenazza         ###   ########.fr       */
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
	{
		write(2, "pwd: too many arguments! \n", 26);
		return (1);
	}
	dir = getcwd((void *)0, 0);
	if (dir)
		printf("%s\n", dir);
	else
	{
		perror("pwd");
		return (1);
	}
	free(dir);
	return (0);
}

// int	ft_cd(t_shell shell)
// {

// }

int	ft_exit(t_shell *shell)
{
	clean_up(shell);
	write(1, "exit\n", 5);
	exit(0);
}
