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

static void	job_put_status(t_job *job, int fd)
{
	int			i;
	int			len;

	if (!job || !job->status)
		return ;
	i = 0;
	len = ft_strlen(job->status);
	ft_putstr_fd(job->status, fd);
	while (len + i++ < 23)
		ft_putchar_fd(' ', fd);
}

static void	job_put_pgid(t_job *job, int fd)
{
	int			i;
	int			len;
	char		*pgid_str;

	if (!job)
		return ;
	i = 0;
	len = 0;
	pgid_str = ft_itoa(job->pgid);
	if (pgid_str)
		len = ft_strlen(pgid_str);
	while (len + i++ < 5)
		ft_putchar_fd(' ', fd);
	if (pgid_str)
		ft_putstr_fd(pgid_str, fd);
}

void	job_put_notif(t_job *job, char option, int fd)
{
	if (!job)
		return ;
	if (option == 'p')
	{
		ft_putnbr_fd(job->pgid, fd);
		ft_putchar_fd('\n', fd);
		return ;
	}
	ft_putchar_fd('[', fd);
	ft_putnbr_fd(job->nbr, fd);
	ft_putchar_fd(']', fd);
	if (job == g_shell->joblst->content)
		ft_putstr_fd("+ ", fd);
	else if (g_shell->joblst->next && job == g_shell->joblst->next->content)
		ft_putstr_fd("- ", fd);
	else
		ft_putstr_fd("  ", fd);
	if (option == 'l')
		job_put_pgid(job, fd);
	ft_putchar_fd(' ', fd);
	job_put_status(job, fd);
	ft_putchar_fd(' ', fd);
	ft_putendl_fd(job->command, fd);
}

int	job_notify(t_job *job_arg, int unnotified_only, char option, int fd)
{
	t_list	*joblst;
	t_job	*job;

	if (job_arg)
	{
		if (job_arg->notified && unnotified_only)
			return (0);
		job_put_notif(job_arg, option, fd);
		job_arg->notified = 1;
		return (0);
	}
	joblst = g_shell->joblst;
	while (joblst)
	{
		job = joblst->content;
		if (!job->notified || !unnotified_only)
		{
			job_put_notif(job, option, fd);
			job->notified = 1;
		}
		joblst = joblst->next;
	}
	return (0);
}
