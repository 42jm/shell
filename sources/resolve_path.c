/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:42:12 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/31 17:47:28 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "quegonza.h"

char	*ft_copy_nodot(char *res, char *str)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (str[i] && str[i + 1])
	{
		if ((!i || str[i - 1] == '/') && !ft_chk_dot(&str[i], "."))
		{
			i += 2;
			nb++;
		}
		else
		{
			res[(i - (nb * 2))] = str[i];
			i++;
		}
	}
	if ((!i || str[i - 1] == '/') && !ft_chk_dot(&str[i], "."))
		return (res);
	res[i - (nb * 2)] = str[i];
	return (res);
}

char	*ft_clear_dot(char *str)
{
	char	*res;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if ((!i || str[i - 1] == '/') && !ft_chk_dot(&str[i], "."))
		{
			i++;
			nb++;
		}
		else
			i++;
	}
	if (!ft_strncmp(&str[i - 2], "/.", 2))
		i++;
	res = (char *)ft_memalloc(i - (nb * 2) + 1);
	if (!res)
		return (NULL);
	res = ft_copy_nodot(res, str);
	return (res);
}

char	*ft_resolve_path(char *str)
{
	char	*path;
	char	*path2;
	char	*tmp;
	int		len;

	if (str[0] != '/')
	{
		tmp = env_getvalue("PWD");
		if (!tmp)
			return (NULL);
		path = ft_path(tmp, str);
	}
	else
		path = ft_strdup(str);
	path = ft_replace_ddots(path);
	path2 = ft_clear_dot(path);
	free(path);
	len = ft_strlen(path2);
	if (len > 1 && path2[len - 1] == '/')
		path2[len - 1] = '\0';
	return (path2);
}
