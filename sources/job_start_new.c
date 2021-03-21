/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_start_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

static int	job_get_next_nbr(void)
{
	t_list	*joblst;
	t_job	*job;
	int		nbr;

	joblst = g_shell->joblst;
	if (!joblst)
		return (1);
	nbr = 0;
	while (joblst)
	{
		job = joblst->content;
		if (job->nbr > nbr)
			nbr = job->nbr;
		joblst = joblst->next;
	}
	return (nbr + 1);
}

int	job_start_new(t_astnode *node)
{
	t_job	*job;
	t_list	*lmnt;

	job = (t_job *)malloc(sizeof(t_job));
	if (!job)
		return (put_error("failed to malloc t_job", "job_start_new"));
	job->command = job_ast2str(node);
	if (!job->command)
		return (1);
	job->pgid = 0;
	job->foreground = 1;
	job->status = ft_strdup("Running");
	job->notified = 1;
	job->nbr = job_get_next_nbr();
	lmnt = (t_list *)malloc(sizeof(t_list));
	if (!lmnt)
		return (put_error("failed to malloc t_list", "job_start_new"));
	lmnt->content = job;
	lmnt->content_size = sizeof(t_job);
	lmnt->next = g_shell->joblst;
	g_shell->joblst = lmnt;
	return (0);
}
