/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:38 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/27 18:22:46 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int c, char **v, char **env)
{
	(void)v;
	if (c == 1)
	{
		if (!ft_strlen(env[0]))
			return (printf("no env found exiting minishell...\n"), 1);
		if (reading_promp(env))
			return (1);
	}
	else
	{
		printf("cant take arguments!\n");
		return (1);
	}
	return (0);
}

