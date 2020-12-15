/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astredir_aggregate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	astredir_aggregate(t_astnode **at, int redir_fd, char *redir_op, char *word)
{
	char	*ptr;

	if (!redir_op || !word || !*word)
		return (put_error("no arguments", "astredir_aggregate"));
	if (!ft_strcmp(word, "-"))
		return (ast_localclose(at, redir_fd));
	ptr = word;
	while (ft_isdigit(*ptr))
		ptr++;
	if (*ptr)
		return (put_error("word following redir_op is not a number", redir_op));
	return (ast_localredir(at, ft_atoi(word), redir_fd));
}
