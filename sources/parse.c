/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_bashvariable(char c)
{
	if (c == '_')
		return (1);
	if (ft_isalnum(c))
		return (1);
	return (0);
}

static int	expand_vars(char **aarg, t_list *envlst)
{
	char	*arg;
	size_t	var_id;
	size_t	var_len;
	char	*var_value;
	char	*tmp;

	var_id = ft_strclen(*aarg, '$');
	while (var_id && aarg[0][var_id])
	{
		arg = *aarg;
		var_len = 0;
		while (is_bashvariable(arg[var_id + var_len]))
			var_len++;
		tmp = ft_strcrop(arg, var_id, var_id + var_len);
		var_value = env_getvalue(envlst, tmp);
		free(tmp);
		arg[var_id - 1] = '\0';
		tmp = ft_strjoin(arg, var_value);
		*aarg = ft_strjoin(tmp, arg + var_id + var_len);
		free(tmp);
		free(arg);
		var_id += ft_strlen(var_value) - 1 + ft_strclen(*aarg + var_id, '$');
	}
	return (0);
}

static int	expand_home(char **aarg, t_list *envlst)
{
	t_list	*home_entry;
	char	*home_value;
	char	*tmp;

	if (ft_strcmp(*aarg, "~") && ft_strncmp(*aarg, "~/", 2))
		return (0);
	home_entry = env_getentry(envlst, "HOME");
	if (!home_entry)
		return (put_error("$HOME does not exist", "expand_home"));
	home_value = ft_strchr(home_entry->content, '=') + 1;
	if (!home_value)
		return (put_error("$HOME holds no value", "expand_home"));
	if (aarg[0][1] == '\0')
	{
		free(*aarg);
		*aarg = ft_strdup(home_value);
		return (0);
	}
	tmp = *aarg;
	*aarg = ft_strjoin(home_value, *aarg + 1);
	free(tmp);
	return (0);
}

static int	expand_any(char **args, t_list *envlst)
{
	while (*args)
	{
		if (expand_vars(args, envlst))
			return (1);
		if (expand_home(args, envlst))
			return (2);
		args++;
	}
	return (0);
}

int			parse_userinput(char *line, char ***aargs, t_list *envlst)
{
	char	*str;
	char	**arr;

	if (!line)
		return (1);
	if (*line == '\0')
	{
		*aargs = (char **)malloc(sizeof(**aargs) * 2);
		(*aargs)[0] = ft_strdup("exit");
		(*aargs)[1] = NULL;
		return (0);
	}
	if (*line == '\n')
	{
		*aargs = NULL;
		return (0);
	}
	if ((str = ft_strchr(line, '\n')))
		*str = '\0';
	else
		pr_putstr_fd("\n", 1);
	*aargs = ft_strcsplit(line, ' ');
	return (expand_any(*aargs, envlst));
}
