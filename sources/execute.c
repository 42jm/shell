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

#include "shell21.h"

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
	else if (!ft_strcmp(*args, "set"))
		ret = builtin_set(argc, args);
	else if (!ft_strcmp(*args, "unset"))
		ret = builtin_unset(argc, args);
	else if (!ft_strcmp(*args, "export"))
		ret = builtin_export(argc, args);
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
	return (-2);
}

int			execute_command(char **args)
{
	pid_t	pid;
	char	*command_path;
	char	**envp;
	int		i;
	int		ret;

	if (!(envp = env_struct_to_strarr(g_envlst)))
		return (2);
	if (get_command_path(args[0], envp, &command_path))
	{
		free_strarr_all(envp);
		return (3);
	}
	if (!(pid = fork()))
		return (pr_execve(command_path, args, envp));
	free_strarr_all(envp);
	free(command_path);
	if (pid > 0)
	{
		waitpid(pid, &i, 0);
		if (WIFEXITED(i) && (ret = env_lastret_set(WEXITSTATUS(i))))
			return (ret);
		return (WIFEXITED(i) ? WEXITSTATUS(i) : 0);
	}
	return (put_error("the shell failed to fork", *args));
}

int			execute(char **args)
{
	static char	*builtins[] = { "echo", "cd", "exit", "set", \
								"unset", "export", NULL };

	if (args == NULL)
		return (put_error("no arguments", "execute"));
	if (ft_arrstr(builtins, *args))
		return (execute_builtin(args));
	if (*args == NULL || (**args == '\0' && args[1] == NULL))
		return (0);
	return (execute_command(args));
}
