/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_quotes(char *line)
{
	size_t	quote_one;
	size_t	quote_two;
	char	*neoline;
	size_t	i;
	size_t	j;

	quote_one = ft_strclen(line, '"');
	quote_two = ft_strclen(line[quote_two], '"');
	if (!quote_one || !quote_two)
		return (ft_strdup(line));
	neoline = (char *)malloc(sizeof(*neoline) * (ft_strlen(line) - 2));
	i = 0;
	while (i < quote_one - 1)
		neoline[i] = line[i++];
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
	return (neoline);
}

static char	**parse_split(char *line)
{
	char	**split;
	char	*neoline;

	
	split = ft_strstrsplit(line, " \t");
	//find neoline in split and replace it with
	free(neoline);
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
	return (expand_any(*aargs, envlst));
}
