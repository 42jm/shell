/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:00:35 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 00:16:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int	g_c;

static int	set_autocomplet_display(int is_set)
{
	if (!is_set)
	{
		is_set = true;
		ft_get_cursor_info();
		g_c = g_info.cursor;
		ft_ctrl_e();
		tputs(tgetstr(DOWN, NULL), g_info.row, ft_putc);
	}
	return (is_set);
}

static void	reset_line_cursor(void)
{
	int	curr;

	curr = g_c;
	while (curr != g_info.cursor)
		ft_mv_left();
	ft_get_cursor_info();
}

static int	ask_choice(int nb_posibility, int max_column)
{
	char		c[7];

	if (max_column && (nb_posibility / max_column >= g_info.row))
	{
		ft_putstr(GREEN);
		ft_putstr("do you want to display ");
		ft_putnbr(nb_posibility);
		ft_putstr(" posibility ? (y)es or (n)o :");
		if (read(0, c, 6))
		{
			if (c[0] == 'n' || c[0] == 'N')
			{
				ft_putchar('\n');
				put_prompt(2);
				ft_putstr(g_info.line);
				reset_line_cursor();
				return (false);
			}
		}
		tputs(tgetstr(DOWN, NULL), g_info.row, ft_putc);
	}
	return (true);
}

static void	space_printing(t_list *curr, size_t len_max,
		int max_column, int is_var)
{
	int	space_left;
	int	curr_idx;

	curr_idx = 0;
	while (curr && curr->content_size)
	{
		space_left = len_max - ft_strlen(curr->content);
		if (curr_idx >= max_column)
		{
			curr_idx = 0;
			tputs(tgetstr(DOWN, NULL), g_info.row, ft_putc);
		}
		ft_putstr(BLUE);
		if (is_var)
			ft_putchar('$');
		ft_putstr(curr->content);
		ft_putstr(COLOR_RESET);
		while (curr && curr->next && space_left-- >= 0)
			ft_putchar(' ');
		curr = curr->next;
		curr_idx++;
	}
}

void	print_completion_choice(int is_var)
{
	t_list	*curr;
	size_t	len_max;
	int		max_column;
	int		nb_posibility;
	int		is_set;

	is_set = 0;
	len_max = get_longest_choice_len();
	if (len_max)
		max_column = (g_info.col - len_max) / len_max;
	curr = g_choice;
	if (curr)
	{
		is_set = set_autocomplet_display(is_set);
		nb_posibility = ft_lstlen(&curr);
		if (ask_choice(nb_posibility, max_column))
		{
			space_printing(curr, len_max, max_column, is_var);
			tputs(tgetstr(DOWN, NULL), g_info.row, ft_putc);
			put_prompt(2);
			ft_putstr(g_info.line);
		}
		reset_line_cursor();
	}
}
