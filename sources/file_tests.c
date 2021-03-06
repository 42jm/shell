/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

int	test_file_validity(char *path)
{
	struct stat	statbuf;

	if (access(path, X_OK))
		return (put_error_ret("File is not executable", path, 2));
	if (stat(path, &statbuf))
		return (put_error_ret("Could not get file status", path, 3));
	if ((statbuf.st_mode & S_IFMT) != S_IFREG)
		return (put_error_ret("File is not regular", path, 4));
	return (0);
}

int	test_empty_path(char *command, char **apath)
{
	if (access(command, F_OK))
		return (put_error_ret("File does not exist", command, 1));
	if (test_file_validity(command))
		return (2);
	*apath = ft_strdup(command);
	return (0);
}

int	test_file_existance(char *command, char **envp, char **apath)
{
	char	**paths;
	int		i;

	if (!ft_strcmp(*envp, "PATH="))
		return (test_empty_path(command, apath));
	paths = ft_strcsplit(*envp + 5, ':');
	i = -1;
	while (paths[++i])
	{
		*apath = ft_strcjoin('/', paths[i], command);
		if (!access(*apath, F_OK))
		{
			free_strarr_all(paths);
			if (!test_file_validity(*apath))
				return (0);
			free(*apath);
			return (3);
		}
		free(*apath);
	}
	free_strarr_all(paths);
	return (put_error_ret("Command not found", command, 4));
}

int	get_command_path(char *command, char **envp, char **apath)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK))
			return (put_error_ret("File does not exist", command, 1));
		if (test_file_validity(command))
			return (2);
		*apath = ft_strdup(command);
		return (0);
	}
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!envp[0])
		return (put_error_ret("PATH var not found in env", command, 3));
	if (test_file_existance(command, envp, apath))
		return (4);
	return (0);
}
