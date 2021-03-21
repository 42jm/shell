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

int	builtin_fg(int argc, char **argv)
{
	t_job	*job;

	if (argc > 2)
		return (ft_putusage("fg", "[job id]"));
	job = NULL;
	if (argc == 1)
	{
		job = jobget_jobid("%+");
		if (!job)
			return (put_error("current", "fg: no such job"));
		return (put_job_in_foreground(job, 1));
	}
	job = jobget_jobid(argv[1]);
	if (!job)
		return (put_error(argv[1], "fg: no such job"));
	return (put_job_in_foreground(job, 1));
}

int	builtin_bg(int argc, char **argv)
{
	char	*jobid;
	t_job	*job;
	int		ret;

	jobid = NULL;
	job = NULL;
	if (argc == 1)
	{
		job = jobget_jobid("%+");
		if (!job)
			return (put_error("current", "bg: no such job"));
		return (put_job_in_background(job, 1));
	}
	ret = 0;
	argv++;
	while (*argv && !ret)
	{
		job = jobget_jobid(*argv);
		if (!job)
			return (put_error(*argv, "bg: no such job"));
		ret = put_job_in_background(job, 1);
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
	int		tmp;

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
		tmp = 0;
		job = jobget_jobid(*argv);
		if (job)
			job_notify(job, 0, opt, 1);
		else
			tmp = put_error(*argv, "jobs: no such job");
		if (tmp)
			ret = tmp;
		argv++;
	}
	job_cleanup(0);
	return (ret);
}
