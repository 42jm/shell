/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/04/02 20:26:56 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

int	job_init_process(t_job *job)
{
	pid_t	pid;

	pid = getpid();
	if (!job->pgid)
		job->pgid = pid;
	if (setpgid(pid, job->pgid) < 0)
		return (put_error("setpgid failed", "job_init_process"));
	if (job->foreground && tcsetpgrp(g_shell->terminal, job->pgid) < 0)
		return (put_error("tcsetpgrp failed", "job_init_process"));
	//signal(SIGINT, SIG_DFL);
	//signal(SIGQUIT, SIG_DFL);
	//signal(SIGTSTP, SIG_DFL);
	//signal(SIGTTIN, SIG_DFL);
	//signal(SIGTTOU, SIG_DFL);
	//signal(SIGCHLD, SIG_DFL);
	//signal(SIGCONT, SIG_DFL);
	return (0);
}

int	put_job_in_foreground(t_job *job, int cont)
{
	int	ret;

	if (tcsetpgrp(g_shell->terminal, job->pgid) < 0)
		return (put_error("setting job as fg", "put_job_in_foreground"));
	if (job->status)
		free(job->status);
	job->status = ft_strdup("Running");
	if (cont)
	{
		if (tcsetattr(g_shell->terminal, TCSADRAIN, &job->tmodes) < 0)
			return (put_error("setting job's tmodes", "put_job_in_foreground"));
		if (kill(-job->pgid, SIGCONT) < 0)
			return (put_error("sending SIGCONT", "put_job_in_foreground"));
	}
	ret = job_wait(job, 0);
	if (tcsetpgrp(g_shell->terminal, g_shell->pgid) < 0)
		return (put_error("setting shell as fg", "put_job_in_foreground"));
	if (tcgetattr(g_shell->terminal, &job->tmodes) < 0)
		return (put_error("saving job's tmodes", "put_job_in_foreground"));
	if (tcsetattr(g_shell->terminal, TCSADRAIN, &g_shell->tmodes) < 0)
		return (put_error("setting shell's tmodes", "put_job_in_foreground"));
	return (ret);
}

int	put_job_in_background(t_job *job, int cont)
{
	if (cont && kill(-job->pgid, SIGCONT) < 0)
		return (put_error("sending SIGCONT", "put_job_in_background"));
	if (job->status)
		free(job->status);
	job->status = ft_strdup("Running");
	return (0);
}
