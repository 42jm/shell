/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_simplecmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	astexec_args(t_astnode *node)
{
	char	**args;
	int		ret;

	if (!(args = ast_to_strarr(node)))
		return (put_error("malloc failed", "astexec_args"));
	ret = execute(args);
	free_strarr_all(args);
	return (ret);
}

int	astexec_simplecmd(t_astnode **at)
{
	int	ret;

	ret = expand_word(*at);
	if (ret)
		return (ret);
	return (astexec_redir(at));
}
