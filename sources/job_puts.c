/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_puts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

void	job_put_nbr(t_job *job, int fd)
{
	ft_putchar_fd('[', fd);
	ft_putnbr_fd(job->nbr, fd);
	ft_putchar_fd(']', fd);
}

void	job_put_currents(t_job *job, int fd)
{
	if (job == jobget_nth_current(0))
		ft_putchar_fd('+', fd);
	else if (job == jobget_nth_current(1))
		ft_putchar_fd('-', fd);
	else
		ft_putchar_fd(' ', fd);
}

void	job_put_pgid(t_job *job, int fd)
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

void	job_put_status(t_job *job, int fd)
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
