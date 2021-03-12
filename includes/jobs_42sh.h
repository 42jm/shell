/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_42sh.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:39:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/01/28 22:17:50 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_42SH_H
# define JOBS_42SH_H

# include "header_42sh.h"

/*
** =====
**
** =====
*/

/*
** ==================
** CONVERT AST TO STR
** ==================
**
**		job_ast2str.c		main file
**	job_ast2str()	calling function, wrapper for main function
**	astcmdstr()		main function, calls op dispatcher or handles word nodes
**	astcmdstr_cpy()	adds str argument to buffer, then updates buffer
*/
char	*job_ast2str(t_astnode *head);
int		astcmdstr(t_astnode *node, char **acmd);
int		astcmdstr_cpy(char **acmd, char *str);

/*
**		job_ast2str_op.c	operator handlers
**	..op_after()	put order: contents,	op,			next
**	..op_before()	put order: op,			contents,	next
**	..op_around()	put order: op_left,		contents,	op_right,	next
**	..op_ignore()	put order: contents,	next
**	..op_heredoc()	put order: next,		heredoc,	word_delim
*/
int		astcmdstr_op_after(t_astnode *node, char **acmd);
int		astcmdstr_op_before(t_astnode *node, char **acmd);
int		astcmdstr_op_around(t_astnode *node, char **acmd);
int		astcmdstr_op_ignore(t_astnode *node, char **acmd);
int		astcmdstr_op_heredoc(t_astnode *node, char **acmd);

/*
**		job_ast2str_get.c	helpers for operator handlers
**	..braces()		op_around helper: return relevent op_left and op_right
*/
void	oparound_get_braces(char *op, char **left, char **right);

#endif
