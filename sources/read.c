/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/01/20 23:20:52 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "quegonza.h"

char	*read_all(int fd)
{
	static ssize_t	buf_size = 1024;
	char			*buf;
	ssize_t			len;

	buf = ft_strnew(buf_size + 1);
	len = read(fd, buf, buf_size);
	if (len == buf_size || len == -1)
	{
		if (buf)
			free(buf);
		return (NULL);
	}
	return (buf);
}

int		format_input(char *in, char ***ainput)
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

int		read_userinput(char ***ainput)
{
	size_t	ret;
	char	*buf;

	buf = ft_get_user_input(&g_info);
	if (!buf && g_info.ctrl_c && !(g_info.ctrl_c &= 0))
		return (130);
	if (!buf)
		return (put_error_ret("failed read", "read_userinput", -1));
	ret = format_input(buf, ainput);
	if (buf)
		free(buf);
	return (ret);
}
