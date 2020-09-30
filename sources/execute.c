/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test_file_validity(char *path)
{
	struct stat	statbuf;

	if (access(path, X_OK))
		return (put_error_ret("file is not executable", path, 1));
	if (stat(path, &statbuf))
		return (put_error_ret("could not get file status", path, 2));
	if ((statbuf.st_mode & S_IFMT) != S_IFREG)
		return (put_error_ret("file is not regular", path, 3));
	return (0);
}

static int	test_file_existance(char *command, char **envp, char **apath)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_strcsplit(*envp + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		*apath = ft_strjoin(tmp, command);
		free(tmp);
		if (!access(*apath, F_OK))
		{
			free_strarr_all(paths);
			if (!test_file_validity(*apath))
				return (0);
			free(*apath);
			return (3);
		}
		free(*apath);
		i++;
	}
	free_strarr_all(paths);
	return (4);
}

static int	get_command_path(char *command, char **envp, char **apath)
{
	char	*tmp;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK))
			return (put_error_ret("file does not exist", command, 1));
		if (test_file_validity(command))
			return (2);
		*apath = ft_strdup(command);
		return (0);
	}
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (test_file_existance(command, envp, apath))
		return (put_error_ret("command not found", command, 3));
	return (0);
}

int			execute_builtin(char **args, t_list *envlst)
{
	int		argc;

	argc = ft_strlen_arr((const char **)args);
	if (!ft_strcmp(*args, "echo"))
		builtin_echo(argc, args);
	else if (!ft_strcmp(*args, "exit"))
		builtin_exit(argc, args);
	else if (!ft_strcmp(*args, "cd"))
		builtin_cd(argc, args, envlst);
	else if (!ft_strcmp(*args, "setenv"))
		builtin_setenv(argc, args, envlst);
	else
		return (put_error_ret("BUILTIN NOT YET IMPLEMENTED", *args, 1));
	return (0);
}

int			execute_command(char **args, t_list *envlst)
{
	pid_t		pid;
	char		*command_path;
	static char	*builtins[] = { "echo", "cd", "exit", "setenv", NULL };
	char		**envp;

	if (args == NULL)
		return (0);
	if (ft_arrstr(builtins, *args))
		return (execute_builtin(args, envlst) ? 1 : 0);
	if (!(envp = ft_lst_to_strarr(envlst)))
		return (2);
	if (get_command_path(args[0], envp, &command_path))
	{
		free_strarr_all(envp);
		return (3);
	}
	if (!(pid = fork()))
	{
		execve(command_path, args, envp);
		put_error("execve error", command_path);
	}
	wait(NULL);
	free_strarr_all(envp);
	free(command_path);
	return (0);
}
