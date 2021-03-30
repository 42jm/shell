/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:30:46 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/30 19:13:21 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

int 	builtin_pwd(int argc, char **argv)
{
	int		opt;
	char	*path;

	(void)argc;
	opt = ft_cd_options(argv);
	if (opt == -1)
		return (ft_error("usage: pwd [-L|-P]\n", 1));
	if (!opt)
	{
		path = env_getvalue("PWD");
		if (!path || !ft_valid_dir(path, path) || ft_strlen(path) > 256)
			opt = 1;
	}
	if (opt)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (ft_error("pwd: getcwd(): error\n", 1));
	}
	ft_putstr(path);
	ft_putchar('\n');
	return (0);
}
