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

int			execute_firstline(char ***alines)
{
	char		**tmp;
	t_astnode	*astroot;
	int			ret;

	tmp = g_lines;
	g_lines = *alines;
	astroot = NULL;
	ret = ast_lexer(*g_lines, &astroot);
	if (!ret)
	{
		g_lines++;
		ret = ast_parser(&astroot);
	}
	if (!ret)
		ret = ast_execute(&astroot);
	if (astroot)
		free_ast(astroot);
	*alines = g_lines;
	g_lines = tmp;
	return (ret);
}

static int	prompt_loop(void)
{
	char	**input;
	char	**aline;
	int		ret;

	input = NULL;
	ret = 0;
	if (!(ret = put_prompt(1)) \
	&& !(ret = read_userinput(0, &input)))
	{
		aline = input;
		while (!ret && aline && *aline)
		{
			ret = execute_firstline(&aline);
			aline++;
		}
	}
	if (input)
		free_strarr_all(input);
	if (ret > 0)
		env_lastret_set(ret);
	return (ret);
}

int			main(int argc, char **argv, char **envp)
{
	int	ret;

	g_lines = NULL;
	signal(SIGINT, sighandle_int);
	ret = env_init(argc, argv, envp);
	while (ret >= 0)
		ret = prompt_loop();
	env_free(g_envlst);
	return (ret < 0 ? -ret - 1 : ret);
}
