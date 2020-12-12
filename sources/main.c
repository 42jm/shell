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

#include "21sh.h"

void		sighandle_ignore(int signum)
{
	(void)signum;
}

void		sighandle_int(int signum)
{
	(void)signum;
	ft_putchar('\n');
	//put_prompt(1, g_envlst);
	ft_putstr("\\_$> ");
	g_childret = 130;
}

int			main(int argc, char **argv, char **envp)
{
	char		**input;
	t_astnode	*astroot;
	t_list		*envlst;
	int			ret;

	(void)argc;
	(void)argv;
	envlst = ft_strarr_to_lst(envp);
	g_childret = 0;
	ret = 0;
	signal(SIGINT, sighandle_int);
	while (ret >= 0)
	{
		g_lines = NULL;
		input = NULL;
		if (!(ret = put_prompt(1, envlst)) \
		&& !(ret = read_userinput(0, &input)))
		{
			while (!ret && g_lines && *g_lines)
			{
				astroot = NULL;
				ret = ast_lexer(*g_lines, &astroot);
				//put_astlexed(astroot);
				if (!ret)
				{
					g_lines++;
					ret = ast_parser(&astroot);
					//put_astparsed(astroot, 0);
				}
				if (!ret)
					ret = expand_word(astroot, envlst);
				if (!ret)
					ret = ast_execute(&astroot, envlst);
				if (astroot)
					free_ast(astroot);
			}
		}
		if (input)
			free_strarr_all(input);
		if (ret > 0)
			g_childret = ret;
	}
	ft_lstfree(envlst);
	return (ret < 0 ? -ret -1 : ret);
}
