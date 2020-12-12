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

int	astexec_args(t_astnode *node, t_list *envlst)
{
	char	**args;
	int		ret;

	//TODO	envir
	if (!(args = ast_to_strarr(node)))
		return (put_error("malloc failed", "astexec_args"));
	ret = execute(args, envlst);
	free_strarr_all(args);
	return (ret);
}

int	astexec_simplecmd(t_astnode **at, t_list *envlst)
{
	//TODO	expand
	return (astexec_redir(at, envlst));
}
