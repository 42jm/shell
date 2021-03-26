/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_blueprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

int	job_set_current(t_job *job)
{
	t_list	*lmnt;
	int		i;

	lmnt = g_shell->joblst;
	i = 0;
	while (lmnt)
	{
		if (lmnt->content == job)
			break ;
		lmnt = lmnt->next;
		i++;
	}
	if (!lmnt)
		return (put_error("job not found in joblst", "job_set_current"));
	lmnt = ft_lstpop(&g_shell->joblst, i);
	if (!lmnt)
		return (put_error("failed to pop job from joblst", "job_set_current"));
	lmnt->next = g_shell->joblst;
	g_shell->joblst = lmnt;
	return (0);
}

int	job_complete_blueprint(void)
{
	t_list	*lmnt;

	if (!g_shell)
		return (put_error("no g_shell", "job_complete_blueprint"));
	if (!g_shell->job_blueprint)
		return (put_error("blueprint disappeared", "job_complete blueprint"));
	if (g_shell->job_blueprint->pgid)
	{
		lmnt = (t_list *)malloc(sizeof(t_list));
		if (!lmnt)
			return (put_error("malloc failed", "job_complete_blueprint"));
		lmnt->content = g_shell->job_blueprint;
		lmnt->content_size = sizeof(t_job);
		ft_lstadd(&g_shell->joblst, lmnt);
	}
	else
		job_free(g_shell->job_blueprint);
	g_shell->job_blueprint = NULL;
	return (0);
}
