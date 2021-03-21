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

int	job_wait(t_job *job)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = waitpid(-1, &status, WUNTRACED);
	if (pid < 0)
		return (put_error("waitpid failed", "job_wait"));
	return (job_update_status(job->pgid, status));
}

int	exejob_wait(pid_t pid)
{
	t_job	*job;
	int		ret;

	job = g_shell->joblst->content;
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
