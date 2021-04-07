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

static void	joblst_pop_free(t_list **ajoblst, t_list *prev, t_job **ajob)
{
	t_list	*next;
	t_list	*joblst;

	joblst = *ajoblst;
	if (prev)
		prev->next = joblst->next;
	else
		g_shell->joblst = joblst->next;
	next = joblst->next;
	job_free(ajob);
	*ajob = NULL;
	free(joblst);
	joblst = next;
	*ajoblst = joblst;
}

int	job_cleanup(int nbr)
{
	t_list	*joblst;
	t_list	*prev;
	t_job	*job;
	int		i;

	joblst = g_shell->joblst;
	prev = NULL;
	i = 0;
	while (joblst)
	{
		job = joblst->content;
		if (!job)
			return (put_error("empty joblst element", "job_cleanup"));
		if (job_should_be_cleaned(job, nbr))
			joblst_pop_free(&joblst, prev, &job);
		else
		{
			prev = joblst;
			joblst = joblst->next;
		}
		i++;
	}
	return (0);
}
