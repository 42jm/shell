/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:38:03 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/09 21:08:46 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_print_t_curs(void)
{
	ft_putstr("\nrow=");
	ft_putnbr(g_info.row);
	ft_putstr(" 	col=");
	ft_putnbr(g_info.col);
	ft_putstr("\ncrsr_row=");
	ft_putnbr(g_info.crsr_row);
	ft_putstr(" 	crsr_col=");
	ft_putnbr(g_info.crsr_col);
	ft_putstr("\ncursor=");
	ft_putnbr(g_info.cursor);
	ft_putstr(" 	strlen=");
	ft_putnbr(g_info.strlen);
	ft_putstr("\n");
}

int		ft_termcap_test(void)
{
	int	val;

	ft_putstr("\\FLAGS/\n");
	val = tgetflag("5i");
	ft_putstr(" 5i[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("am");
	ft_putstr(" am[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("bs");
	ft_putstr(" bs[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("bw");
	ft_putstr(" bw[");
	ft_putnbr(val);
	ft_putstr("]\n");
	val = tgetflag("da");
	ft_putstr(" da[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("bd");
	ft_putstr(" bd[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("eo");
	ft_putstr(" eo[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("es");
	ft_putstr(" es[");
	ft_putnbr(val);
	ft_putstr("]\n");
	val = tgetflag("gn");
	ft_putstr(" gn[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("hc");
	ft_putstr(" hc[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("HC");
	ft_putstr(" HC[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("hs");
	ft_putstr(" hs[");
	ft_putnbr(val);
	ft_putstr("]\n");
	val = tgetflag("hz");
	ft_putstr(" hz[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("in");
	ft_putstr(" in[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("km");
	ft_putstr(" km[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("mi");
	ft_putstr(" mi[");
	ft_putnbr(val);
	ft_putstr("]\n");
	val = tgetflag("ms");
	ft_putstr(" ms[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("NF");
	ft_putstr(" NF[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("NP");
	ft_putstr(" NP[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("NR");
	ft_putstr(" NR[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("nx");
	ft_putstr(" nx[");
	ft_putnbr(val);
	ft_putstr("]\n");
	val = tgetflag("os");
	ft_putstr(" os[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("ul");
	ft_putstr(" ul[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("xb");
	ft_putstr(" xb[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("xn");
	ft_putstr(" xn[");
	ft_putnbr(val);
	ft_putstr("]\n");
	val = tgetflag("xo");
	ft_putstr(" xo[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("xs");
	ft_putstr(" xs[");
	ft_putnbr(val);
	ft_putstr("]");
	val = tgetflag("xt");
	ft_putstr(" xt[");
	ft_putnbr(val);
	ft_putstr("]");
	ft_putstr("\n/_____\\\n");
	return (0);
}

void	chk21(void)
{
	char *term_type;

	ft_get_cursor_info();
	term_type = getenv("TERM");
	ft_putstr("TERM=");
	ft_putstr(term_type);
	ft_putstr("\n");
	ft_print_t_curs();
	ft_termcap_test();
}
