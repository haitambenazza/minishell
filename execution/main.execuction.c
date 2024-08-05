/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.execuction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:05:33 by tkoulal           #+#    #+#             */
/*   Updated: 2024/08/05 13:53:37 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_last_return_value(int pid)
{
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	return (0);
}

void	check_exit_status(t_shell *node)
{
	if (g_exit_status == 1)
		g_exit_status = 1;
	close_fd(node->infile, node->outfile);
}

int	run_exec(t_shell *cmds)
{
	t_shell	*tmp;
	int		status;
	int		i;

	tmp = cmds;
	status = 0;
	i = -1;
	while (tmp)
	{
		execute(tmp);
		if (g_exit_status)
			check_exit_status(tmp);
		tmp = tmp->next;
	}
	tmp = cmds;
	while (tmp && tmp->next)
		tmp = tmp->next;
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status) && cmds->size > 1)
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
	while (wait(NULL) > 0)
		;
	return (0);
}

int	execution(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
	if (!tmp)
		return (0);
	tmp->pid = 0;
	g_exit_status = 0;
	cmds->size = cmds_size(cmds);
	handle_herdoc(cmds);
	set_hold(cmds);
	if (cmds->next == NULL && !is_built_in(cmds) && !cmds->redirection)
	{
		if_built_in_run(cmds);
		return (0);
	}
	else if (run_exec(cmds) == ERROR)
		return (ERROR);
	unlick_files(tmp);
	return (0);
}
