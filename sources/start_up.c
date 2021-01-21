/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 06:31:50 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/07 07:39:15 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

/*
** FT_TERMCAP_INIT() :
** Gets terminal type from GETENV()
** Then load its capabilities from termcap data base with TGETENT()
*/

int		ft_termcap_init(void)
{
	int ret;
	char *term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_putstr("TERM variable is not set.\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		ft_putstr("Can't access to the termcap database.\n");
	else if (ret == 0)
	{
		ft_putstr("Invalid terminal type.\n");
		return (-1);
	}
	return (ret);
}

/*
** FT_GET_CAP() :
** Gets all string capabilities needed with TGETSTR() and stores them
*/

int		ft_get_cap(t_cap *cap)
{
	if (!(cap->cd = tgetstr("cd", NULL)))
		return (ft_error("`cd' capability not found", 0));
	if (!(cap->ce = tgetstr("ce", NULL)))
		return (ft_error("`ce' capability not found", 0));
	if (!(cap->cm = tgetstr("cm", NULL)))
		return (ft_error("`cm' capability not found", 0));
	if (!(cap->dc = tgetstr("dc", NULL)))
		return (ft_error("`dc' capability not found", 0));
	/*
	if (!(cap->le = tgetstr("le", NULL)))
		return (ft_error("`le' capability not found", 0));
	if (!(cap->nd = tgetstr("nd", NULL)))
		return (ft_error("`nd' capability not found", 0));
		*/
	return (1);
}

/*
** FT_START_UP() :
** flag 'ICANON' - Non-canonical mode. Read() does not wait '\n'.
** flag 'ECHO'   - Keyboard touches are not printed on terminal.
*/

int		ft_start_up(void)
{
	struct termios	s_termios;

	if (ft_termcap_init() < 1)
		return (0);
	if (tcgetattr(0, &s_termios) == -1)
		return (0);
	g_info.s_termios_backup = s_termios;
	g_info.ctrl_c = 0;
	g_info.copy = NULL;
	s_termios.c_lflag &= ~(ICANON);
	s_termios.c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, &s_termios) == -1)
		return (0);
	if (!ft_get_cap(&(g_info.cap)))
		return (ft_error("ft_get_cap(): terminal capability missing\n", 0));
	if (!ft_history_init())
		return (0);
	return (1);
}