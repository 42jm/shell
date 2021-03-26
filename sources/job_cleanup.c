/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

static void	joblst_del(void *content, size_t content_size)
{
	t_job	*job;

	(void)content_size;
	job = content;
	if (!job)
		return ;
	job_free(&job);
}

static int	job_should_be_cleaned(t_job *job, int nbr)
{
	if (!job)
		return (0);
	if (nbr)
	{
		if (nbr == job->nbr)
			return (1);
		return (0);
	}
	if (!job->notified)
		return (0);
	if (!ft_strncmp(job->status, "Done", 4))
		return (1);
	if (!ft_strncmp(job->status, "Terminated", 10))
		return (1);
	return (0);
}

int	job_cleanup(int nbr)
{
	t_list	*joblst;
	t_list	*todel;
	t_job	*job;
	int		i;

	joblst = g_shell->joblst;
	i = 0;
	while (joblst)
	{
		job = joblst->content;
		if (!job)
			return (put_error("empty joblst element", "job_cleanup"));
		joblst = joblst->next;
		if (job_should_be_cleaned(job, nbr))
		{
			todel = ft_lstpop(&g_shell->joblst, i);
			if (todel)
				ft_lstdelone(&todel, &joblst_del);
		}
		i++;
	}
	return (0);
}
