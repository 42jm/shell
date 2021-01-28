/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/01/28 22:12:41 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "quegonza.h"

char		**g_lines;
t_list		*g_envlst;
t_curs		g_info;

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

int			execute_all_lines(char **aline)
{
	int	ret;

	ret = 0;
	while (!ret && aline && *aline)
	{
		ret = execute_firstline(&aline);
		if (aline && *aline)
			aline++;
	}
	return (ret);
}

int			prompt_loop(void)
{
	char	**input;
	int		ret;

	input = NULL;
	ret = put_prompt(1);
	if (!ret && !(ret = read_userinput(&input)))
		ret = execute_all_lines(input);
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
	if (!ft_start_up())
		return (ft_error("Initialization error\n", 1));
//	signal(SIGINT, sighandle_int);
	ret = env_init(argc, argv, envp);
	while (ret >= 0)
		ret = prompt_loop();
	env_free(g_envlst);
	ft_end_clean(NULL);
	return (ret < 0 ? -ret - 1 : ret);
}
