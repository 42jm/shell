/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/04/07 09:28:07 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "quegonza.h"
#include "jobs_42sh.h"

char	*read_all(int fd)
{
	static ssize_t	buf_size = 1024;
	char			*buf;
	ssize_t			len;
	char			*ret;
	char			*tmp;

	buf = ft_strnew(buf_size + 1);
	if (!buf)
		return (NULL);
	len = read(fd, buf, buf_size);
	ret = NULL;
	while (len && len != -1)
	{
		if (ret)
		{
			tmp = ret;
			ret = ft_strjoin(ret, buf);
			free(tmp);
		}
		else
			ret = ft_strdup(buf);
		len = read(fd, buf, buf_size);
	}
	free(buf);
	return (ret);
}

int 	format_input(char *in, char ***ainput)
{
	char	*buf;

	if (!in)
		return (put_error("no arguments", "ainput"));
	buf = ft_strdup(in);
	if (!*buf)
	{
		free(buf);
		buf = ft_strdup("\n");
	}
	*ainput = ft_strcsplit_all(buf, '\n');
	free(buf);
	if (!*ainput)
		return (put_error("strsplit failed", "read_userinput"));
	return (0);
}

int 	read_userinput(char ***ainput)
{
	size_t	ret;
	char	*buf;

	if (g_shell->is_interactive)
		buf = ft_get_user_input();
	else
	{
		buf = read_all(0);
		if (!ft_strlen(buf))
		{
			free(buf);
			return (-1);
		}
	}
	if (!buf && g_info.sigcont)
	{
		return (put_error_ret(" can't set terminal after suspension.",
				NULL, -1));
	}
	if (!buf)
		return (put_error_ret("failed read", "read_userinput", -1));
	ret = format_input(buf, ainput);
	if (buf)
		free(buf);
	return (ret);
}
