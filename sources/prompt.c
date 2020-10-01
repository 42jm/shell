/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_prompt(int fd, t_list *envlst)
{
	char	*prompt;

	prompt = env_getvalue(envlst, "PS1");
	if (!prompt)
		prompt="$> ";
	if (pr_putstr_fd(prompt, fd) > 0)
		return (put_error("Could not print prompt", NULL));
	return (0);
}
