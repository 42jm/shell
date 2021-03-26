/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

static int	pipe_dupexe(t_astnode **at, int *fildes, int io)
{
	int	ret;

	if (io != 0 && io != 1)
		return (put_error("argument io is neither 1 nor 0", "pipe_dupexe"));
	if (close(fildes[1 - io]) == -1)
		return (put_error("failed to close unused pipe fd", "pipe_dupexe"));
	ret = ast_localredir(at, fildes[io], io);
	if (close(fildes[io]) == -1)
		return (put_error("failed to close used pipe fd", "pipe_dupexe"));
	return (ret);
}

static int	pipejob_child(t_astnode **at)
{
	char	*ret;

	g_shell->is_interactive = 0;
	if (job_init_process(g_shell->job_blueprint))
		exit(1);
	if (astexec_pipe(at))
		exit(1);
	ret = env_getvalue("?");
	if (ret)
		exit(ft_atoi(ret));
	exit(1);
	return (-2);
}

static int	pipejob_parent(pid_t pid)
{
	int	ret;

	g_shell->job_blueprint->pgid = pid;
	if (setpgid(pid, pid) < 0)
		put_error("setpgid failed", "pipejob_parent");
	ret = put_job_in_foreground(g_shell->job_blueprint, 0);
	if (!ret)
		return (job_complete_blueprint());
	job_free(&g_shell->job_blueprint);
	g_shell->job_launched = 0;
	return (ret);
}

static int	pipexec_job(t_astnode **at)
{
	int		ret;
	pid_t	pid;

	ret = job_start_new(*at);
	if (ret)
		return (ret);
	g_shell->job_launched = 1;
	pid = fork();
	if (pid == -1)
	{
		job_free(&g_shell->job_blueprint);
		return (put_error("failed fork", "pipexec_job"));
	}
	if (!pid)
		ret = pipejob_child(at);
	else
		ret = pipejob_parent(pid);
	g_shell->job_launched = 0;
	return (ret);
}

int	astexec_pipe(t_astnode **at)
{
	int			fildes[2];
	pid_t		pid;
	t_astnode	*node;

	if (!at || !*at)
		return (put_error("no arguments", "astexec_pipe"));
	if (g_shell->is_interactive && !g_shell->job_blueprint)
		return (pipexec_job(at));
	node = *at;
	if (!node->content || !node->next)
		return (put_error("a pipe needs two commands", node->op));
	if (pipe(fildes) == -1)
		return (put_error("failed to create pipe", node->op));
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", node->op));
	if (!pid)
	{
		pipe_dupexe((t_astnode **)&node->content, fildes, 1);
		exit(0);
		return (-2);
	}
	return (pipe_dupexe((t_astnode **)&node->next, fildes, 0));
}
