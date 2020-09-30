/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_userinput(char *line, char ***aargs)
{
	char	*str;
	char	**arr;

	if (!line)
		return (1);
	if (*line == '\0')
	{
		*aargs = (char **)malloc(sizeof(**aargs) * 2);
		(*aargs)[0] = ft_strdup("exit");
		(*aargs)[1] = NULL;
		return (0);
	}
	if (*line == '\n')
	{
		*aargs = NULL;
		return (0);
	}
	if ((str = ft_strchr(line, '\n')))
		*str = '\0';
	else
		pr_putstr_fd("\n", 1);
	*aargs = ft_strcsplit(line, ' ');
	return (0);
}
