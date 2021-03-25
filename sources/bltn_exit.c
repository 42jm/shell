/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:00:40 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

static t_job	*bltn_exit_get_first_stopped_job(void)
{
	t_list	*joblst;
	t_job	*job;

	joblst = g_shell->joblst;
	while (joblst)
	{
		job = joblst->content;
		if (job && !ft_strncmp(job->status, "Stopped", 7))
			return (job);
		joblst = joblst->next;
	}
	return (NULL);
}

int	builtin_exit(int argc, char **argv)
{
	int		ret;
	t_job	*stopped_job;

	pr_putstr_fd("exit\n", 2);
	if (argc > 2)
		put_error("Too many arguments", *argv);
	ret = -1;
	if (argc == 2 && ft_isdigit((int)argv[1][0]))
		ret = -1 * (ft_atoi(argv[1]) + 1);
	else if (argc == 2)
		return (put_error_ret("Numeric argument required", argv[1], 2));
	stopped_job = bltn_exit_get_first_stopped_job();
	if (stopped_job && !g_shell->exit_warning)
	{
		g_shell->exit_warning = 2;
		return (put_error_ret("There are stopped jobs", argv[1], 3));
	}
	while (stopped_job)
	{
		ret = -149;
		kill(-stopped_job->pgid, SIGKILL);
		job_cleanup(stopped_job->nbr);
		stopped_job = bltn_exit_get_first_stopped_job();
	}
	return (ret);
}
