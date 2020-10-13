/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_quotes(char *line)
{
	size_t	quote_one;
	size_t	quote_two;
	char	*neoline;
	char 	*tmp;
	size_t	i;
	size_t	j;

	quote_one = ft_strclen(line, '"');
	quote_two = quote_one + ft_strclen(line + quote_one, '"');
	if (!quote_one || quote_two == quote_one)
		return (ft_strdup(line));
	neoline = (char *)malloc(sizeof(*neoline) * (ft_strlen(line) - 1));
	i = 0;
	while (i < quote_one - 1)
	{
		neoline[i] = line[i];
		i++;
	}
	while (i < quote_two - 2)
	{
		neoline[i] = line[i + 1];
		if (neoline[i] == ' ')
			neoline[i] = 1;
		if (neoline[i] == '\t')
			neoline[i] = 2;
		i++;
	}
	tmp = parse_quotes(line + quote_two);
	j = 0;
	while (tmp[j])
		neoline[i++] = tmp[j++];
	free(tmp);
	neoline[i] = '\0';
	return (neoline);
}

static char	**parse_split(char *line)
{
	char	*neoline;
	char	**split;
	char	**arr;

	neoline = parse_quotes(line);
	split = ft_strstrsplit(neoline, " \t");
	free(neoline);
	arr = split;
	while (arr && *arr)
	{
		while ((neoline = ft_strchr(*arr, 1)))
			*neoline = ' ';
		while ((neoline = ft_strchr(*arr, 2)))
			*neoline = '\t';
		arr++;
	}
	return(split);
}

int			parse_userinput(char *line, char ***aargs, t_list *envlst)
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
	if ((str = ft_strchr(line, '\n')))
		*str = '\0';
	else
		pr_putstr_fd("\n", 1);
	*aargs = parse_split(line);
	ft_putstr_arr(*aargs, ft_strlen_arr((const char **)*aargs));
	return (expand_any(*aargs, envlst));
}
