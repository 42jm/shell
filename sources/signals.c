/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/02/23 18:47:35 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

void	sighandle_chld(int signum)
{
	(void)signum;
	job_update_status(NULL);
}

void	sighandle_tstp(int signum)
{
	(void)signum;
	ft_putchar('\n');
	env_set("?", "148", 0);
}

void	sighandle_int(int signum)
{
	(void)signum;
	ft_putchar('\n');
	env_set("?", "130", 0);
}
