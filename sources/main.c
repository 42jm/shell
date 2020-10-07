/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 17:46:27 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	t_list	*envlst;

	envlst = ft_strarr_to_lst(envp);
	while (1)
	{
		if (put_prompt(1, envlst))
			return (1);
		if (read_userinput(0, &line))
			return (2);
		if (parse_userinput(line, &args, envlst))
			return (3);
		if (execute_any(args, envlst) < 0)
			break ;
		if (args)
			free_strarr_all(args);
		if (line)
			free(line);
	}
	ft_lstfree(envlst);
	return (0);
}
