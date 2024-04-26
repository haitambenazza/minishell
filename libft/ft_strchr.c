/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:36:46 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/25 10:02:59 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
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
