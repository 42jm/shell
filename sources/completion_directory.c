/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_directory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 23:02:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 00:50:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

static int	compare_file(DIR *current, char *name)
{
	struct dirent	*directory;
	int				count;

	count = 0;
	if (current)
	{
		directory = readdir(current);
		while (directory)
		{
			if (ft_strnequ(directory->d_name, name, ft_strlen(name)) || !name)
			{
				g_choice = make_choice(directory->d_name);
				count++;
			}
			directory = readdir(current);
		}
	}
	return (count);
}

int	is_directory(char *word, int is_path, int *insert_idx)
{
	DIR		*current;
	char	*path_name;
	char	*name;
	int		count;

	count = 0;
	path_name = NULL;
	if (is_path)
	{
		name = ft_strrchr(word, '/') + 1;
		*insert_idx = ft_strlen(name);
		path_name = ft_strndup(word, ft_strlen(word) - *insert_idx);
		current = opendir(path_name);
	}
	else
	{
		current = opendir(".");
		name = word;
	}
	count = compare_file(current, name);
	ft_strdel(&path_name);
	if (!closedir(current))
		return (count);
	return (-1);
}
