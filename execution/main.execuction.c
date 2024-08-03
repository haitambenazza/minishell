/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.execuction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:05:33 by tkoulal           #+#    #+#             */
/*   Updated: 2024/08/03 22:34:53 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exit_status(t_shell *node)
{
	if (g_exit_status == 1)
		g_exit_status = 1;
	else
		g_exit_status = 127;
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
		if (execute(tmp) == 0) //just why?
			;
		else
			check_exit_status(tmp);
		tmp = tmp->next;
	}
	tmp = cmds;
	while (tmp && tmp->next) //wtf??!
		tmp = tmp->next;
	waitpid(tmp->pid, &status, 0);
	if (WIFEXITED(status) && cmds->size > 1)
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	while (wait(NULL) > 0)
	;
	return (0);
}

int	execution(t_shell *cmds)
{
	t_shell	*tmp;

	tmp = cmds;
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
