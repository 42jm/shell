/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/02/14 20:00:29 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

int	put_prompt(int fd)
{
	char	*prompt;

	if (!g_shell->is_interactive)
		return (0);
	prompt = env_getvalue("PS1");
	if (!prompt)
	{
		if (!getuid())
			prompt = "\\_#> ";
		else
			prompt = "\033[01;32m\\_$\033[00m> ";
	}
	job_notify(NULL, 1, 0, 2);
	job_cleanup(0);
	if (pr_putstr_fd(prompt, fd) > 0)
		return (put_error("Could not print prompt", NULL));
	return (0);
}
