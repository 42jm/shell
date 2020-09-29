/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lstfree(void *ptr, size_t sz)
{
	free(ptr);
	sz = 0;
}

int			main(int argc, char **argv)
{
	char	*line;
	char	**args;
	t_list	*envlst;

	envlst = ft_strarr_to_lst(__environ);
	while (1)
	{
		if (put_prompt(1))
			return (1);
		if (read_userinput(0, &line))
			return (2);
		if (parse_userinput(line, &args))
			return (3);
		if (execute_command(args, envlst) < 0)
			return (4);
		if (args)
			free_strarr_all(args);
		if (line)
			free(line);
	}
	ft_lstdel(&envlst, &lstfree);
	return (0);
}
