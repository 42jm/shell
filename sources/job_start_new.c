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

int	jobget_next_nbr(void)
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

	if (g_shell->job_blueprint)
		return (put_error("job blueprint already exists", "job_start_new"));
	job = (t_job *)malloc(sizeof(t_job));
	if (!job)
		return (put_error("failed to malloc t_job", "job_start_new"));
	job->command = job_ast2str(node);
	if (!job->command)
	{
		free(job);
		return (1);
	}
	job->pgid = 0;
	if (tcgetattr(g_shell->terminal, &job->tmodes) < 0)
		put_error("setting current terminal modes as default", "job_start_new");
	job->foreground = 1;
	job->status = ft_strdup("Running");
	job->notified = 1;
	job->nbr = jobget_next_nbr();
	g_shell->job_blueprint = job;
	return (0);
}
