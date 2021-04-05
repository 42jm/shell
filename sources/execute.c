/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/04/03 03:39:01 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

int	execute_builtin(char **bltn_names, char **args)
{
	int	argc;
	int	ret;
	int	id;

	static int (*bltn_funcs[])(int, char **) = {
builtin_alias, builtin_unalias, builtin_pwd, \
builtin_echo, builtin_exit, builtin_cd, \
builtin_set, builtin_unset, builtin_export, \
builtin_setenv, builtin_unsetenv, builtin_env, \
builtin_jobs, builtin_fg, builtin_bg, builtin_type};
	argc = ft_strlen_arr((const char **)args);
	id = ft_arrstr_id(bltn_names, *args);
	if (id < 0)
		return (put_error_ret("BUILTIN NOT YET IMPLEMENTED", *args, 1));
	ret = (*bltn_funcs[id])(argc, args);
	env_lastret_set(ret);
	return (ret);
}

static int	pr_execve(char *command_path, char **args, char **envp)
{
	if (g_shell->is_interactive && g_shell->job_blueprint)
		if (job_init_process(g_shell->job_blueprint))
			return (-2);
	execve(command_path, args, envp);
	put_error("Execve error", command_path);
	free_strarr_all(envp);
	free(command_path);
	return (-2);
}

static int	execmd_wait(pid_t pid)
{
	int		i;
	int		ret;

	waitpid(pid, &i, 0);
	if (WIFEXITED(i))
	{
		ret = env_lastret_set(WEXITSTATUS(i));
		if (ret)
			return (ret);
	}
	if (WIFEXITED(i))
		return (WEXITSTATUS(i));
	if (WIFSIGNALED(i))
		return (WTERMSIG(i));
	return (0);
}

int	execute_command(char **args)
{
	pid_t	pid;
	char	*command_path;
	char	**envp;

	envp = env_struct_to_strarr(g_envlst);
	if (!envp)
		return (2);
	if (get_command_path(args[0], envp, &command_path))
	{
		free_strarr_all(envp);
		return (3);
	}
	pid = fork();
	if (!pid)
		return (pr_execve(command_path, args, envp));
	free_strarr_all(envp);
	free(command_path);
	if (pid > 0 && g_shell->is_interactive && !g_shell->job_launched)
		return (exejob_wait(pid));
	else if (pid > 0)
		return (execmd_wait(pid));
	return (put_error("the shell failed to fork", *args));
}

int	execute(char **args)
{
	static char	*bltn_names[] = {
		"alias", "unalias", "pwd", \
		"echo", "exit", "cd", \
		"set", "unset", "export", \
		"setenv", "unsetenv", "env", \
		"jobs", "fg", "bg", "type", NULL};

	if (args == NULL)
		return (put_error("no arguments", "execute"));
	if (ft_arrstr(bltn_names, *args))
		return (execute_builtin(bltn_names, args));
	if (*args == NULL || (**args == '\0' && args[1] == NULL))
		return (0);
	if (**args == '\0')
		return (put_error("command is empty", "execute"));
	return (execute_command(args));
}
