/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:16:41 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/02 15:23:20 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z') \
			&& (str[i] < 'A' || str[i] > 'Z') && str[i] != '_')
		{
			write(2, "name is not a valid shell variable name\n", 40);
			return (1);
		}
		i++;
	}
	return (0);
}
