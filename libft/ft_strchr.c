/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:36:46 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/16 17:38:12 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcount(char *s, char chr)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == chr)
			c++;
		i++;
	}
	return (c);
}

char	*ft_strchr(char *s, int c)
{
	size_t			i;
	unsigned char	char_c;

	i = 0;
	char_c = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == char_c)
			return ((char *)(s + i));
		i++;
	}
	if (char_c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
