/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

static void	jobupdate_stopped(t_job *job, int status)
{
	if (WSTOPSIG(status) == SIGSTOP)
		job->status = ft_strdup("Stopped (SIGSTOP)");
	else if (WSTOPSIG(status) == SIGTTIN)
		job->status = ft_strdup("Stopped (SIGTTIN)");
	else if (WSTOPSIG(status) == SIGTTOU)
		job->status = ft_strdup("Stopped (SIGTTOU)");
	else
		job->status = ft_strdup("Stopped");
	job->notified = 0;
}

static void	jobupdate_terminated(t_job *job, int status)
{
	char	*sigstr;
	char	*tmp;

	if (WTERMSIG(status) == SIGINT)
	{
		sighandle_int(SIGINT);
		job->notified = 1;
	}
	else
		job->notified = 0;
	sigstr = sig_int2str(WTERMSIG(status));
	if (!sigstr)
		sigstr = ft_itoa(WTERMSIG(status));
	if (!sigstr)
		return ;
	tmp = sigstr;
	sigstr = ft_strjoin(sigstr, ")");
	free(tmp);
	if (!sigstr)
		return ;
	job->status = ft_strjoin("Terminated (", sigstr);
	free(sigstr);
}

static void	jobupdate_exited(t_job *job, int status)
{
	char	*sigstr;
	char	*tmp;

	job->notified = job->foreground;
	if (!WIFEXITED(status))
	{
		job->status = ft_strdup("Done");
		return ;
	}
	tmp = ft_itoa(WEXITSTATUS(status));
	if (tmp)
		env_set("?", tmp, 0);
	if (!ft_strcmp(tmp, "0"))
	{
		job->status = ft_strdup("Done");
		return ;
	}
	sigstr = ft_strjoin("Done(", tmp);
	free(tmp);
	if (!sigstr)
		return ;
	job->status = ft_strjoin(sigstr, ")");
	free(sigstr);
}

int	job_update_status(pid_t pgid, int status)
{
	t_job	*job;

	job = jobget_pgid(pgid);
	if (!job)
		return (0);
	if (job->status)
		free(job->status);
	if (WIFSTOPPED(status))
		jobupdate_stopped(job, status);
	else if (WIFSIGNALED(status))
		jobupdate_terminated(job, status);
	else
		jobupdate_exited(job, status);
	if (!job->status)
		return (put_error("malloc failed", "job_update_status"));
	return (0);
}
