/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:42:26 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/28 18:45:57 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

char	*ft_bad_option(char *cmd_name, char option, char *message)
{
	ft_putstr(cmd_name);
	ft_putstr(": -");
	ft_putchar(option);
	ft_putstr(": ");
	ft_putstr(message);
	ft_putstr("\n");
	return (NULL);
}

char	*ft_addchr_to_str(char *s, char c)
{
	int		len;
	char	*res;

	if (!s)
		s = ft_memalloc(1);
	if (!s)
	{
		ft_putstr("malloc(): error\n");
		return (NULL);
	}
	len = ft_strlen(s);
	res = ft_memalloc(len + 2);
	ft_strcpy(res, s);
	res[len] = c;
	free(s);
	return (res);
}

char	*ft_get_options(char **argv, char *allowed)
{
	int		i;
	int		j;
	char	*options;

	options = NULL;
	i = 0;
	while (argv[++i] && argv[i][0] == '-' && argv[i][1])
	{
		j = 0;
		while (argv[i][++j])
		{
			if (ft_strchr(allowed, argv[i][j]))
			{
				options = ft_addchr_to_str(options, argv[i][j]);
				if (!options)
					return (NULL);
			}
			else
				return (ft_bad_option(argv[0], argv[i][j], "invalid option"));
		}
	}
	if (options)
		return (options);
	return (" ");
}

int 	ft_count_args(int argc, char **argv)
{
	int	i;
	int	ret;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1])
		i++;
	ret = 0;
	while (i < argc)
	{
		i++;
		ret++;
	}
	return (ret);
}
