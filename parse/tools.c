/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:59:45 by hbenazza          #+#    #+#             */
/*   Updated: 2024/06/25 12:08:32 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_malloc(char *str, char **arr, int *len)
{
	int	i;

	arr[*len] = malloc((ft_strlen(str) + 1));
	if (!arr[*len])
		return ;
	i = 0;
	while (str[i])
	{
		arr[*len][i] = str[i];
		i++;
	}
	arr[*len][i] = 0;
	*len += 1;
}

int	lst_size(char **lst)
{
	int	len;

	len = 0;
	while (lst[len])
		len++;
	return (len);
}

void	copy_char(char *out, char *str, int *len, int *i)
{
	out[*len] = str[*i];
	*i += 1;
	*len += 1;
}
