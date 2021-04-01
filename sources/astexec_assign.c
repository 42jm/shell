/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

static int	node_isassign(t_astnode *node)
{
	char	*word;
	size_t	len;

	if (!node || !node->content || node->op)
		return (0);
	word = node->content;
	len = ft_strclen(word, '=');
	if (len < 2)
		return (0);
	if (ft_strchr("#?0123456789", *word))
		return (0);
	if (bashvar_len(word) != len - 1)
		return (0);
	return (1);
}

static int	node_isassign_all(t_astnode *node)
{
	while (node)
	{
		if (!node_isassign(node))
			return (0);
		node = node->next;
	}
	return (1);
}

static int	assign_local_reset(char *name, char *value, bool exportable)
{
	t_envvar	*var;

	var = env_getvar(name);
	if (var && !var->local)
		return (0);
	if (!value)
		return (env_unset(name));
	return (env_set(name, value, exportable));
}

static int	assign_local(t_astnode *node, char *name, char *value)
{
	int			ret;
	t_envvar	*og_var;
	char		*og_value;
	bool		og_exportable;
	t_envvar	*new_var;

	og_value = NULL;
	og_exportable = 1;
	og_var = env_getvar(name);
	if (og_var && og_var->value)
		og_value = ft_strdup(og_var->value);
	if (og_var)
		og_exportable = og_var->exportable;
	ret = env_set(name, value, 1);
	new_var = env_getvar(name);
	if (!og_var && new_var)
		new_var->local = 1;
	if (!ret)
		ret = astexec_assign(node->next);
	assign_local_reset(name, og_value, og_exportable);
	if (og_value)
		free(og_value);
	return (ret);
}

int	astexec_assign(t_astnode *node)
{
	int		ret;
	char	*name;
	char	*value;
	int		all_assign;

	if (!node)
		return (0);
	if (!node_isassign(node))
		return (astexec_args(node));
	name = ft_strcdup(node->content, '=');
	value = ft_strchr(node->content, '=');
	if (value)
		value = expand_str(value + 1);
	all_assign = node_isassign_all(node);
	if (all_assign)
		ret = env_set(name, value, -1);
	else
		ret = assign_local(node, name, value);
	if (name)
		free(name);
	if (value)
		free(value);
	if (ret || !all_assign)
		return (ret);
	return (astexec_assign(node->next));
}
