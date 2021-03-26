/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notifs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

static void	job_put_notif(t_job *job, char option, int fd)
{
	if (!job)
		return ;
	if (option == 'p')
	{
		ft_putnbr_fd(job->pgid, fd);
		ft_putchar_fd('\n', fd);
		return ;
	}
	job_put_nbr(job, fd);
	job_put_currents(job, fd);
	ft_putchar_fd(' ', fd);
	if (option == 'l')
		job_put_pgid(job, fd);
	ft_putchar_fd(' ', fd);
	job_put_status(job, fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(job->command, fd);
	if (!ft_strcmp(job->status, "Running") && !job->foreground)
		ft_putstr_fd(" &", fd);
	ft_putchar_fd('\n', fd);
}

int	job_notify(t_job *job_arg, int unnotified_only, char option, int fd)
{
	t_job	*job;
	int		n;
	int		next_nbr;

	if (job_arg)
	{
		if (job_arg->notified && unnotified_only)
			return (0);
		job_put_notif(job_arg, option, fd);
		job_arg->notified = 1;
		return (0);
	}
	next_nbr = jobget_next_nbr();
	n = 0;
	while (++n < next_nbr)
	{
		job = jobget_number(n);
		if (job && (!job->notified || !unnotified_only))
		{
			job_put_notif(job, option, fd);
			job->notified = 1;
		}
	}
	return (0);
}
