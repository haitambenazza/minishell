/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:38 by hbenazza          #+#    #+#             */
/*   Updated: 2024/07/25 17:02:39 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_status;

int	main(int c, char **v, char **env)
{
	(void)v;
	if (c == 1)
	{
		if (reading_promp(env))
			return (exit_status);
	}
	else
	{
		printf("cant take arguments!\n");
		return (1);
	}
	return (exit_status);
}

