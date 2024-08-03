/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:38:23 by hbenazza          #+#    #+#             */
/*   Updated: 2024/08/03 22:38:54 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_infile_acces(char *file_name)
{
	int	status;

	status = access(file_name, F_OK);
	if (status == -1)
	{
		perror(file_name);
		return (-1);
	}
	else
	{
		status = open(file_name, O_RDONLY);
		if (status == -1)
		{
			perror(file_name);
			return (-1);
		}
		else
			return (status);
	}
	return (ERROR);
}
