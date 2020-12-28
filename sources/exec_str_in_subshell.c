/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_str_in_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int	exec_subshell(int *sub_out, char *in)
{
	int		tmp;
	int		ret;
	int		ret_nice;
	char	**in_arr;

	if (close(sub_out[0]) == -1)
		return (put_error("failed to closed unused pipe", "exec_subshell"));
	if ((tmp = dup(1)) == -1)
		return (put_error("failed to backup stdout", "exec_subshell"));
	if (dup2(sub_out[1], 1) == -1)
		return (put_error("failed to set new stdout", "exec_subshell"));
	in_arr = NULL;
	if (!(ret = format_input(in, &in_arr)))
		ret = execute_all_lines(in_arr);
	if (!(ret_nice = 0) && in_arr)
		free_strarr_all(in_arr);
	if (dup2(tmp, 1) == -1)
		ret_nice = put_error("failed to reset to og stdout", "exec_subshell");
	if (close(tmp) == -1)
		ret_nice = put_error("failed to close stdout backup", "exec_subshell");
	if (close(sub_out[1]) == -1)
		ret_nice = put_error("failed to closed used pipe", "exec_subshell");
	if (!ret && ret_nice)
		ret = ret_nice;
	return (ret);
}

static int	read_subshell(int *sub_out, char **aout)
{
	int		ret;

	if (close(sub_out[1]) == -1)
		return (put_error("failed to closed unused pipe", "read_subshell"));
	*aout = read_all(sub_out[0]);
	if (!*aout)
		ret = 1;
	if (close(sub_out[0]) == -1)
		ret = put_error("failed to closed used pipe", "read_subshell");
	return (ret);
}

int			exec_str_in_subshell(char *in, char **aout)
{
	int		sub_out[2];
	pid_t	pid;
	int		ret;

	if (!in)
		return (put_error("no arguments", "exec_str_in_subshell"));
	if (*in == '\0')
		return ((*aout = ft_strdup("")) ? 0 : put_error("malloc failed", NULL));
	if (pipe(sub_out) == -1 || (pid = fork()) == -1)
		return (put_error("pipe/fork failed", "exec_str_in_subshell"));
	if (!pid)
	{
		ret = exec_subshell(sub_out, in);
		return (ret < 0 ? ret : -ret - 1);
	}
	ret = read_subshell(sub_out, aout);
	if (!ret && waitpid(pid, NULL, 0) == -1)
		ret = put_error("waitpid failed", "exec_str_in_subshell");
	if (ret && *aout)
	{
		free(*aout);
		*aout = NULL;
	}
	return (ret);
}
