/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

int	job_wait_any(int options)
{
	pid_t	pid;
	t_job	*job;
	int		status;

	status = 0;
	pid = waitpid(WAIT_ANY, &status, options);
	while (pid > 0)
	{
		job = jobget_pgid(pid);
		job_set_status(job, status);
		status = 0;
		pid = waitpid(WAIT_ANY, &status, options);
	}
	return (0);
}

int	job_wait(t_job *job, int nohang)
{
	int		status;
	int		options;

	status = 0;
	options = WUNTRACED;
	if (nohang)
		options = WUNTRACED | WNOHANG | WCONTINUED;
	if (!job)
		return (job_wait_any(options));
	if (waitpid(job->pgid, &status, options) < 0)
		return (put_error("waitpid failed", "job_wait"));
	if (job)
		return (job_set_status(job, status));
	return (0);
}

int	exejob_wait(pid_t pid)
{
	t_job	*job;
	int		ret;

	job = g_shell->job_blueprint;
	if (!job)
		return (put_error("blueprint disappeared", "exejob_wait"));
	if (!job->pgid)
		job->pgid = pid;
	if (setpgid(pid, job->pgid) < 0)
		return (put_error("setpgid failed", "exejob_wait"));
	if (job->foreground)
		ret = put_job_in_foreground(job, 0);
	else
		ret = put_job_in_background(job, 0);
	return (ret);
}
