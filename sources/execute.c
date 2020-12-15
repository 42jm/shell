/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			execute_builtin(char **args)
{
	int	argc;
	int	ret;

	argc = ft_strlen_arr((const char **)args);
	if (!ft_strcmp(*args, "echo"))
		ret = builtin_echo(argc, args);
	else if (!ft_strcmp(*args, "exit"))
		ret = builtin_exit(argc, args);
	else if (!ft_strcmp(*args, "cd"))
		ret = builtin_cd(argc, args);
	else if (!ft_strcmp(*args, "setenv"))
		ret = builtin_setenv(argc, args);
	else if (!ft_strcmp(*args, "unsetenv"))
		ret = builtin_unsetenv(argc, args);
	else
		ret = put_error_ret("BUILTIN NOT YET IMPLEMENTED", *args, 1);
	return (ret);
}

static int	pr_execve(char *command_path, char **args, char **envp)
{
	execve(command_path, args, envp);
	put_error("Execve error", command_path);
	free_strarr_all(envp);
	free(command_path);
	return (-1);
}

int			execute_command(char **args)
{
	pid_t	pid;
	char	*command_path;
	char	**envp;
	int		wstatus;

	if (!(envp = env_struct_to_strarr(g_envlst)))
		return (2);
	if (get_command_path(args[0], envp, &command_path))
	{
		free_strarr_all(envp);
		return (3);
	}
	if (!(pid = fork()))
		return (pr_execve(command_path, args, envp));
	if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_childret = WEXITSTATUS(wstatus);
	}
	free_strarr_all(envp);
	free(command_path);
	if (pid == -1)
		return (put_error("the shell failed to fork", *args));
	return (0);
}

int			execute(char **args)
{
	static char	*builtins[] = { "echo", "cd", "exit", "setenv", \
								"unsetenv", NULL };

	if (args == NULL)
		return (put_error("no arguments", "execute"));
	if (ft_arrstr(builtins, *args))
		return (execute_builtin(args));
	if (*args == NULL || (**args == '\0' && args[1] == NULL))
		return (0);
	return (execute_command(args));
}
