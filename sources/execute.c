//execute.c/////////////////////////////////////////////////////////////////////

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

static int	get_command_path(char *command, char **envp, char **apath)
{
	char	**paths;
	char	*tmp;
	int		i;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK))
			return (put_error_ret("file does not exist", command, 1));
		if (test_file_validity(command))
			return (2);
		*apath = ft_strdup(command);
		return (0);
	}
	//get strarr of paths from envp
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	paths = ft_strcsplit(*envp + 5, ':');
	i = 0;
	while (paths[i])
	{
		//verify existance of file
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
	put_error("command not found", command);
	free_strarr_all(paths);
	return (4);
}

int			execute_builtin(char **args)
{
	int		argc;

	argc = ft_strlen_arr((const char **)args);
	if (!ft_strcmp(*args, "echo"))
		builtin_echo(argc, args);
	else if (!ft_strcmp(*args, "exit"))
		builtin_exit(argc, args);
	else
		return (put_error_ret("BUILTIN NOT YET IMPLEMENTED", *args, 1));
	return (0);
}

int			execute_command(char **args, t_list *envlst)
{
	pid_t		pid;
	char		*command_path;
	static char	*builtins[] = { "echo", "cd", "exit", NULL };
	/*
	static char	*envp[] = {
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/bin",
		NULL };
	*/
	char		**envp;

	//return on empty
	if (args == NULL)
		return (0);
	//execute if builtin
	if (ft_arrstr(builtins, *args))
	{
		if (execute_builtin(args))
			return (1);
		return (0);
	}
	//envp strarr from list
	envp = ft_lst_to_strarr(envlst);
	if (!envp)
		return (2);
	//get command full path
	if (get_command_path(args[0], envp, &command_path))
	{
		free_strarr_all(envp);
		return (3);
	}
	//execute args[0] with args + 1 as subprocess
	pid = fork();
	if (!pid)
	{
		execve(command_path, args, envp);
		put_error("execve error", command_path);
		free_strarr_all(envp);
		free(command_path);
		return (-1);
	}
	wait(NULL);
	free_strarr_all(envp);
	free(command_path);
	return (0);
}
