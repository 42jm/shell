/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		envput_export(void)
{
	t_list		*entry;
	t_envvar	*var;

	entry = g_envlst;
	while (entry)
	{
		var = entry->content;
		if (var->exportable)
		{
			ft_putstr("export ");
			ft_putstr(var->name);
			if (var->value)
			{
				ft_putstr("=\"");
				ft_putstr(var->value);
				ft_putchar('"');
			}
			ft_putchar('\n');
		}
		entry = entry->next;
	}
	return (0);
}

int		env_put(bool exportonly)
{
	t_list		*entry;
	t_envvar	*var;

	entry = g_envlst;
	while (entry)
	{
		var = entry->content;
		if (!exportonly || var->exportable)
		{
			ft_putstr(var->name);
			ft_putchar('=');
			if (var->value)
				ft_putstr(var->value);
			ft_putchar('\n');
		}
		entry = entry->next;
	}
	return (0);
}
