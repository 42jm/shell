/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	read_userinput(int fd, char ***ainput)
{
	ssize_t	ret;
	char	*buf;

	buf = ft_strnew(MAX_INPUT_LENGTH);
	ret = read(fd, buf, MAX_INPUT_LENGTH);
	if (ret < 0)
	{
		put_error("Failed read on input", NULL);
		free(buf);
		return (1);
	}
	if (ret >= MAX_INPUT_LENGTH)
	{
		put_error("Input too long", NULL);
		free(buf);
		return (2);
	}
	if (!*buf)
	{
		free(buf);
		buf = ft_strdup("exit");
		if (!buf)
			return (put_error("failed to strdup 'exit'", NULL));
	}
	g_lines = ft_strcsplit_all(buf, '\n');
	*ainput = g_lines;
	if (!g_lines)
	{
		put_error("strsplit failed", "read_userinput");
		free(buf);
		return (3);
	}
	//ft_putstr_arr(g_lines);
	free(buf);
	return (0);
}
