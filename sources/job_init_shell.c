/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_init_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

static int	jobinit_interactive(void)
{
	pid_t	term_pgid;

	term_pgid = tcgetpgrp(g_shell->terminal);
	while (term_pgid != g_shell->pgid)
	{
		if (term_pgid < 0)
			return (put_error("tcgetpgrp failed", "jobinit_interactive"));
		kill(-g_shell->pgid, SIGTTIN);
		term_pgid = tcgetpgrp(g_shell->terminal);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	g_shell->pgid = getpid();
	if (setpgid(g_shell->pgid, g_shell->pgid) < 0)
		return (put_error("giving 42sh its own pgid", "jobinit_interactive"));
	if (tcsetpgrp(g_shell->terminal, g_shell->pgid) < 0)
		return (put_error("setting 42sh as foreground", "jobinit_interactive"));
	if (tcgetattr(g_shell->terminal, &g_shell->tmodes) < 0)
		return (put_error("saving the terminal modes", "jobinit_interactive"));
	return (0);
}

int	job_init_shell(void)
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	if (!g_shell)
		return (put_error("malloc failed", "job_init_shell"));
	g_shell->pgid = getpgrp();
	g_shell->joblst = NULL;
	g_shell->terminal = STDIN_FILENO;
	g_shell->is_subshell = 0;
	g_shell->is_interactive = isatty(g_shell->terminal);
	g_shell->job_blueprint = NULL;
	if (g_shell->is_interactive)
		return (jobinit_interactive());
	return (0);
}
