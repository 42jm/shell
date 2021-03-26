/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_separ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

int	astexec_andor(t_astnode **at)
{
	t_astnode	*node;
	int			ret;
	char		*lastret;
	int			is_lastret;

	node = *at;
	ret = 0;
	lastret = env_getvalue("?");
	if (!lastret)
		return (put_error("envir_var '?' is not set", "astexec_andor"));
	is_lastret = ft_strcmp(lastret, "0");
	if (!ft_strcmp(node->op, "&&") && !is_lastret)
		ret = ast_execute((t_astnode **)&node->content);
	else if (!ft_strcmp(node->op, "||") && is_lastret)
		ret = ast_execute((t_astnode **)&node->content);
	if (ret < 0)
		return (ret);
	return (ast_execute((t_astnode **)&node->next));
}

static int	amperexec_child(t_astnode *node, int job_spawned)
{
	g_shell->is_interactive = 0;
	if (job_spawned && job_init_process(g_shell->job_blueprint))
		exit(1);
	g_shell->job_launched = 1;
	ast_execute((t_astnode **)&node->content);
	exit(0);
	return (-2);
}

static int	amperexec_parent(t_astnode *node, int job_spawned, pid_t pid)
{
	if (job_spawned)
	{
		g_shell->job_blueprint->pgid = pid;
		job_put_nbr(g_shell->job_blueprint, 2);
		ft_putchar_fd(' ', 2);
		ft_putnbr_fd(pid, 2);
		ft_putchar_fd('\n', 2);
		if (setpgid(pid, pid) < 0)
			put_error("setpgid failed", "amperexec_parent");
		if (job_complete_blueprint())
			put_error("failed to complete blueprint", "amperexec_parent");
	}
	env_set("?", "0", 0);
	return (ast_execute((t_astnode **)&node->next));
}

int	astexec_amper(t_astnode **at)
{
	pid_t		pid;
	t_astnode	*node;
	int			ret;
	int			job_spawned;

	node = *at;
	job_spawned = 0;
	if (g_shell->is_interactive && !g_shell->job_blueprint)
	{
		ret = job_start_new(node->content);
		if (ret)
			return (ret);
		job_spawned = 1;
		g_shell->job_blueprint->foreground = 0;
	}
	pid = fork();
	if (pid == -1 && job_spawned)
		job_free(&g_shell->job_blueprint);
	if (pid == -1)
		return (put_error("failed fork", node->op));
	if (!pid)
		return (amperexec_child(node, job_spawned));
	return (amperexec_parent(node, job_spawned, pid));
}

int	astexec_semicol(t_astnode **at)
{
	t_astnode	*node;
	int			ret;

	node = *at;
	ret = ast_execute((t_astnode **)&node->content);
	if (ret < 0)
		return (ret);
	return (ast_execute((t_astnode **)&node->next));
}
