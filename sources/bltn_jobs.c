/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:00:40 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

static int	bltn_fg_update_notif_run(char *jobid)
{
	t_job	*job;

	job = jobget_jobid(jobid);
	if (!job)
		return (put_error(jobid, "fg: no such job"));
	if (job->status && (!ft_strncmp(job->status, "Done", 4) || \
!ft_strncmp(job->status, "Terminated", 10)))
		return (put_error(job->command, "fg: job has terminated"));
	if (job->status)
		free(job->status);
	job->status = ft_strdup("Running");
	job->foreground = 1;
	job->notified = 1;
	job_set_current(job);
	ft_putendl(job->command);
	return (put_job_in_foreground(job, 1));
}

int	builtin_fg(int argc, char **argv)
{
	t_job	*job;

	if (argc > 2)
		return (ft_putusage("fg", "[job id]"));
	job = NULL;
	if (argc == 1)
		return (bltn_fg_update_notif_run("%+"));
	return (bltn_fg_update_notif_run(argv[1]));
}

static int	bltn_bg_update_notif_run(char *jobid)
{
	t_job	*job;

	job = jobget_jobid(jobid);
	if (!job)
		return (put_error(jobid, "bg: no such job"));
	if (job->status && (!ft_strncmp(job->status, "Done", 4) || \
!ft_strncmp(job->status, "Terminated", 10)))
		return (put_error(job->command, "bg: job has terminated"));
	if (job->status && !ft_strcmp(job->status, "Running"))
		return (put_error(job->command, "bg: job already in background"));
	if (job->status)
		free(job->status);
	job->status = ft_strdup("Running");
	job->foreground = 0;
	job->notified = 1;
	job_set_current(job);
	job_put_nbr(job, 1);
	job_put_currents(job, 1);
	ft_putchar(' ');
	ft_putstr(job->command);
	ft_putendl(" &");
	return (put_job_in_background(job, 1));
}

int	builtin_bg(int argc, char **argv)
{
	char	*jobid;
	t_job	*job;
	int		ret;
	int		tmp;

	jobid = NULL;
	job = NULL;
	if (argc == 1)
		return (bltn_bg_update_notif_run("%+"));
	ret = 0;
	argv++;
	while (*argv)
	{
		tmp = bltn_bg_update_notif_run(*argv);
		if (tmp)
			ret = tmp;
		argv++;
	}
	return (ret);
}

int	builtin_jobs(int argc, char **argv)
{
	char	*options;
	char	opt;
	t_job	*job;
	int		ret;

	options = ft_optset(&argc, &argv, "lp");
	if (!options)
		return (ft_putusage("jobs", "[-l|-p] [job id...]"));
	opt = ft_strlast(options);
	free(options);
	if (!*argv)
		job_notify(NULL, 0, opt, 1);
	ret = 0;
	while (*argv)
	{
		job = jobget_jobid(*argv);
		if (job)
			job_notify(job, 0, opt, 1);
		else if (put_error(*argv, "jobs: no such job") && !ret)
			ret = 1;
		argv++;
	}
	job_cleanup(0);
	return (ret);
}
