/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:36:45 by tkoulal           #+#    #+#             */
/*   Updated: 2024/08/05 13:40:18 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_heredoc(char *line)
{
	int		i;
	int		len;
	char	*new_line;
	char	*temp;

	i = 0;
	len = len_of_env(line);
	new_line = malloc(len + 1);
	new_line[len] = 0;
	temp = new_line;
	new_line = get_env_to_line(new_line, line);
	free(temp);
	free(line);
	return (new_line);
}

int	reading_promp_her(int *fd, t_redirect *red_tmp)
{
	char	*line;
	int		flag;

	flag = 0;
	line = NULL;
	*fd = open(red_tmp->herdoc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("~> ");
		if (!line)
			return (ctrl_d_her(), 1);
		if (ft_strchr(line, '$'))
		{
			line = expand_heredoc(line);
			flag = 1;
		}
		if (free_if_there_is_a_del(&flag, line, red_tmp) == 0)
			break ;
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		if (flag == 0)
			free(line);
	}
	return (0);
}

void	open_herdoc(t_shell *cmds)
{
	int			pid;
	t_shell		*node;
	t_redirect	*red_tmp;
	int			fd;
	int			save_fd;

	pid = fork();
	save_fd = 0;
	fd = 0;
	if (!pid)
	{
		signal(SIGINT, ctrl_c_her);
		node = cmds;
		red_tmp = cmds->redirection;
		while (node)
		{
			red_tmp = node->redirection;
			prompt_reading_heredoc(red_tmp, fd);
			node = node->next;
		}
		dup2(save_fd, STDIN_FILENO);
		exit(0);
	}
	else
		get_last_return_value(pid);
}

int	handle_herdoc(t_shell *cmds)
{
	t_shell		*node;
	t_redirect	*red_tmp;
	int			i;

	i = 0;
	node = cmds;
	red_tmp = cmds->redirection;
	while (node)
	{
		red_tmp = node->redirection;
		while (red_tmp)
		{
			if (red_tmp->type == HERDOC)
			{
				red_tmp->herdoc_name = generate_name(i);
			}
			red_tmp = red_tmp->next;
		}
		i++;
		node = node->next;
	}
	open_herdoc(cmds);
	return (0);
}

void	unlick_files(t_shell *tmp)
{
	t_redirect	*tmp_red;

	while (tmp && tmp->redirection)
	{
		tmp_red = tmp->redirection;
		while (tmp_red)
		{
			if (tmp_red->type == 13)
			{
				unlink(tmp_red->herdoc_name);
			}
			tmp_red = tmp_red->next;
		}
		tmp = tmp->next;
	}
}
