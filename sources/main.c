/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/04/05 23:48:15 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "quegonza.h"
#include "jobs_42sh.h"

char		**g_lines = NULL;
t_list		*g_envlst = NULL;
t_curs		g_info;
t_shell		*g_shell = NULL;
t_alias		*g_alias = NULL;

int	execute_firstline(char ***alines)
{
	char		**tmp;
	t_astnode	*astroot;
	int			ret;

	tmp = g_lines;
	g_lines = *alines;
	astroot = NULL;
	ret = 0;
	if (!*g_lines)
		ret = 1;
	if (!ret)
		ret = ast_lexer(*g_lines, &astroot);
	g_lines++;
	if (!ret)
		ret = ast_parser(&astroot);
	if (!ret)
		ret = ast_execute(&astroot);
	if (astroot)
		free_ast(astroot);
	*alines = g_lines;
	g_lines = tmp;
	return (ret);
}

int	execute_all_lines(char **aline)
{
	int ret;

	ret = 0;
	while (aline && *aline)
	{
		ret = execute_firstline(&aline);
		if (ret)
			env_lastret_set(ret);
	}
	return (ret);
}

int	prompt_loop(void)
{
	char	**input;
	int		ret;

	input = NULL;
	ret = put_prompt(2);
	if (!ret)
		ret = read_userinput(&input);
	if (!ret)
		ret = execute_all_lines(input);
	if (input)
	{
		free_strarr(input, ft_strlen_arr((const char **)input));
		free(input);
	}
	if (ret > 0)
		env_lastret_set(ret);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*lastret;

	ret = job_init_shell();
	if (ret)
		return (ret);
	if (g_shell->is_interactive && !ft_start_up())
		return (ft_error("Initialization error\n", 1));
	ret = env_init(argc, argv, envp);
	while (ret >= 0)
		ret = prompt_loop();
	lastret = env_getvalue("?");
	if (ft_strcmp(lastret, "0"))
		ret = ft_atoi(lastret);
	env_free(g_envlst);
	if (g_shell->is_interactive)
		ft_end_clean(NULL);
	if (ret < 0)
		return (-ret - 1);
	return (ret);
}
