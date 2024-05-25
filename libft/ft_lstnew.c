/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:17:13 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/24 16:39:12 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	string_special(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == 1)
				cmd[i][j] = '|';
			else if (cmd[i][j] == 2)
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
}

t_shell	*ft_lstnew(char *str)
{
	t_shell	*node;

	(void)str;
	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	if (str)
		node->cmd = ft_split(str, ' ');
	string_special(node->cmd);
	node->next = NULL;
	return (node);
}

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (*str != '=')
		str ++;
	if (*str == '=')
		str++;
	while (str[i])
		i++;
	value = malloc((i + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (*str)
	{
		value[i] = *(str++);
		i++;
	}
	value[i] = 0;
	return (value);
}

t_env	*ft_lstnew2(char *str)
{
	t_env	*node;

	(void)str;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = get_key(str);
	node->value = get_value(str);
	node->next = NULL;
	return (node);
}
