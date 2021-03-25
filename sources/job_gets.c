/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_gets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:00:40 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

t_job	*jobget_pgid(pid_t pgid)
{
	t_list	*joblst;
	t_job	*job;

	joblst = g_shell->joblst;
	while (joblst)
	{
		job = joblst->content;
		if (job && job->pgid == pgid)
			return (job);
		joblst = joblst->next;
	}
	return (NULL);
}

t_job	*jobget_nth_current(size_t n)
{
	t_list	*joblst;
	t_job	*job;
	size_t	i;

	i = 0;
	joblst = g_shell->joblst;
	while (joblst && i <= n)
	{
		job = joblst->content;
		if (!job)
			return (NULL);
		if (i == n)
			return (job);
		i++;
		joblst = joblst->next;
	}
	return (NULL);
}

t_job	*jobget_number(int n)
{
	t_list	*joblst;
	t_job	*job;

	joblst = g_shell->joblst;
	if (!joblst)
		return (NULL);
	job = joblst->content;
	while (joblst && job && job->nbr != n)
	{
		joblst = joblst->next;
		if (joblst)
			job = joblst->content;
		else
			job = NULL;
	}
	return (job);
}

static t_job	*jobget_command(char *str, int anchored)
{
	t_list	*joblst;
	t_job	*job;
	t_job	*ret_job;
	int		i;

	joblst = g_shell->joblst;
	if (!joblst)
		return (NULL);
	i = 0;
	ret_job = NULL;
	while (joblst)
	{
		job = joblst->content;
		if (!job)
			return (NULL);
		if (anchored && !ft_strncmp(job->command, str, ft_strlen(str)) && ++i)
			ret_job = job;
		if (!anchored && !ft_strstr(job->command, str) && ++i)
			ret_job = job;
		joblst = joblst->next;
	}
	if (i < 2)
		return (ret_job);
	put_error(str, "jobget_command: ambiguous job id");
	return (NULL);
}

t_job	*jobget_jobid(char *job_id)
{
	int		nbr;

	if (!job_id)
		return (NULL);
	if (ft_strlen(job_id) != 1 && *job_id == '%')
		job_id++;
	if (ft_strlen(job_id) == 1 && ft_strchr("%+", *job_id))
		return (jobget_nth_current(0));
	if (!ft_strcmp(job_id, "-"))
		return (jobget_nth_current(1));
	nbr = ft_atoi_strict(job_id);
	if (nbr != -1)
		return (jobget_number(nbr));
	if (*job_id != '?')
		return (jobget_command(job_id, 1));
	return (jobget_command(job_id, 0));
}
