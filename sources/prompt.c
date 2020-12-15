/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 17:46:59 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	put_prompt(int fd)
{
	char	*prompt;

	prompt = env_getvalue("PS1");
	if (!prompt)
		prompt = "\\_$> ";
	if (pr_putstr_fd(prompt, fd) > 0)
		return (put_error("Could not print prompt", NULL));
	return (0);
}
