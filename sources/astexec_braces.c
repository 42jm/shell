/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_braces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

int	astexec_curly(t_astnode **at)
{
	t_astnode	*head;
	t_astnode	*node;
	static char	*authorized_ops[4] = {";", "()", "{}", NULL };

	head = *at;
	node = head->content;
	if (head->next)
		return (put_error("a token is following the braces", "{}"));
	if (!node)
		return (put_error("nothing inside braces", "{}"));
	if (node->op && !ft_arrstr(authorized_ops, node->op))
		return (put_error("unauthorized op inside braces", node->op));
	return (ast_execute(&node));
}

static int	parenexec_child(t_astnode *node, int job_spawned)
{
	char	*ret;

	g_shell->is_interactive = 0;
	if (job_spawned && job_init_process(g_shell->job_blueprint))
		exit(1);
	ast_execute(&node);
	ret = env_getvalue("?");
	if (ret)
		exit(ft_atoi(ret));
	return (-2);
}

static int	parenexec_parent(t_astnode *head, int job_spawned, pid_t pid)
{
	int		ret;
	int		wstatus;

	if (job_spawned)
	{
		g_shell->job_blueprint->pgid = pid;
		if (setpgid(pid, pid) < 0)
			put_error("setpgid failed", "parenexec_parent");
		ret = put_job_in_foreground(g_shell->job_blueprint, 0);
		return (ast_execute(&head->next));
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		ret = env_lastret_set(WEXITSTATUS(wstatus));
		if (ret)
			return (ret);
	}
	return (ast_execute(&head->next));
}

int	astexec_paren(t_astnode **at)
{
	t_astnode	*head;
	pid_t		pid;
	int			job_spawned;

	head = *at;
	if (head->next)
		return (put_error("a token is following the parentheses", head->op));
	job_spawned = 0;
	if (g_shell->is_interactive && !g_shell->job_launched)
	{
		g_shell->job_launched = 1;
		job_spawned = 1;
	}
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", head->op));
	if (!pid)
		return (parenexec_child((*at)->content, job_spawned));
	return (parenexec_parent(head, job_spawned, pid));
}
