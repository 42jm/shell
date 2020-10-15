/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:09:52 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	t_list	*envlst;
	int		ret;

	envlst = ft_strarr_to_lst(envp);
	ret = 0;
	while (ret >= 0)
	{
		if ((ret = put_prompt(1, envlst)))
			break ;
		if ((ret = read_userinput(0, &line)))
			break ;
		if ((ret = parse_userinput(line, &args, envlst)))
			break ;
		ret = execute_any(args, envlst);
		if (args)
			free_strarr_all(args);
		if (line)
			free(line);
	}
	ft_lstfree(envlst);
	if (ret < 0)
		return (-ret - 1);
	return (ret);
}
