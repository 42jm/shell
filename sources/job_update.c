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
	if (WSTOPSIG(status) == SIGTSTP)
		sighandle_tstp(SIGTSTP);
	job->notified = 0;
}

static void	jobupdate_terminated(t_job *job, int status)
{
	char	*sigstr;
	char	*tmp;

	job->notified = 0;
	if (WTERMSIG(status) == SIGINT)
	{
		sighandle_int(SIGINT);
		job->notified = 1;
	}
	sigstr = sig_int2str(WTERMSIG(status));
	if (!sigstr)
		sigstr = ft_itoa(WTERMSIG(status));
	if (!sigstr)
	{
		put_error("malloc failed", "jobupdate_terminated");
		return ;
	}
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
	char	*ret;

	job->notified = job->foreground;
	ret = ft_itoa(WEXITSTATUS(status));
	if (!ret)
	{
		put_error("itoa failed", "jobupdate_exited");
		return ;
	}
	env_set("?", ret, 0);
	if (!ft_strcmp(ret, "0"))
	{
		job->status = ft_strdup("Done");
		free(ret);
		return ;
	}
	sigstr = ft_strjoin("Done(", ret);
	free(ret);
	if (!sigstr)
		return ;
	job->status = ft_strjoin(sigstr, ")");
	free(sigstr);
}

int	job_set_status(t_job *job, int status)
{
	char	*old_status;

	if (!job)
		return (0);
	old_status = job->status;
	if (WIFSTOPPED(status))
		jobupdate_stopped(job, status);
	else if (WIFSIGNALED(status))
		jobupdate_terminated(job, status);
	else if (WIFCONTINUED(status))
		job->status = ft_strdup("Running");
	else if (WIFEXITED(status))
		jobupdate_exited(job, status);
	else
		return (0);
	if (old_status)
		free(old_status);
	if (!job->status)
		return (put_error("malloc failed", "job_set_status"));
	return (0);
}

int	job_update_status(t_job *job)
{
	if (job && ft_strncmp(job->status, "Done", 4) && \
ft_strncmp(job->status, "Terminated", 10))
		return (job_wait(job, 1));
	else if (job)
		return (0);
	return (job_wait(NULL, 1));
}
