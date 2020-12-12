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

int	execute_builtin(char **args, t_list *envlst)
{
	int	argc;
	int	ret;

	argc = ft_strlen_arr((const char **)args);
	if (!ft_strcmp(*args, "echo"))
		ret = builtin_echo(argc, args);
	else if (!ft_strcmp(*args, "exit"))
		ret = builtin_exit(argc, args);
	else if (!ft_strcmp(*args, "cd"))
		ret = builtin_cd(argc, args, envlst);
	else if (!ft_strcmp(*args, "setenv"))
		ret = builtin_setenv(argc, args, envlst);
	else if (!ft_strcmp(*args, "unsetenv"))
		ret = builtin_unsetenv(argc, args, envlst);
	else if (!ft_strcmp(*args, "env"))
		ret = builtin_env(argc, args, envlst);
	else
		ret = put_error_ret("BUILTIN NOT YET IMPLEMENTED", *args, 1);
	return (ret);
}

int	execute_command(char **args, t_list *envlst)
{
	pid_t	pid;
	char	*command_path;
	char	**envp;
	int		wstatus;

	if (!(envp = ft_lst_to_strarr(envlst)))
		return (2);
	if (get_command_path(args[0], envp, &command_path))
	{
		free_strarr_all(envp);
		return (3);
	}
	pid = fork();
	if (!pid)
	{
		execve(command_path, args, envp);
		put_error("Execve error", command_path);
		free_strarr_all(envp);
		free(command_path);
		return (-1);
	}
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

int	execute(char **args, t_list *envlst)
{
	//int			ret;
	static char	*builtins[] = { "echo", "cd", "exit", "setenv", \
								"unsetenv", "env", NULL };

	if (args == NULL)
		return (put_error("no arguments", "execute"));
	if (ft_arrstr(builtins, *args))
		return (execute_builtin(args, envlst));
	if (*args == NULL || (**args == '\0' && args[1] == NULL))
		return (0);
	return (execute_command(args, envlst));
}
