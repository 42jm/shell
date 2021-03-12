/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmdstr_opget.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

void	oparound_get_braces(char *op, char **left, char **right)
{
	if (!ft_strcmp(op, "{}"))
	{
		*left = ft_strdup("{ ");
		*right = ft_strdup(" }");
	}
	else if (!ft_strcmp(op, "()"))
	{
		*left = ft_strdup("( ");
		*right = ft_strdup(" )");
	}
	else if (!ft_strcmp(op, "<()"))
	{
		*left = ft_strdup("<( ");
		*right = ft_strdup(" )");
	}
	else if (!ft_strcmp(op, ">()"))
	{
		*left = ft_strdup(">( ");
		*right = ft_strdup(" )");
	}
}
