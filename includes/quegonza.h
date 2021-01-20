/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quegonza.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 03:16:03 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/20 22:20:37 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEGONZA_H
# define QUEGONZA_H
# include "libft.h"
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

# define CTRL_A	1
# define CTRL_D	4
# define CTRL_E	5
# define CTRL_U	21
# define CTRL_W	23
# define CTRL_Y	25
# define ESC	27
# define DEL	127

typedef struct	s_cap
{
	char		*cd;
	char		*ce;
	char		*cm;
	char		*dc;
//	char		*le;
//	char		*nd;
}				t_cap;

typedef struct		s_curs
{
	int				row;
	int				col;
	int				crsr_row;
	int				crsr_col;
	int				cursor;
	int				strlen;
	int				prompt;
	int				hist_pos;
	char			**hist;
	char			*line;
	char			*copy;
	char			ctrl_c;
	struct termios	s_termios_backup;
	t_cap			cap;
}					t_curs;

t_curs				g_info;

int		ft_start_up(void);
int		ft_termcap_init(void);
int		ft_get_cap(t_cap *cap);
void	ft_input_init();
char	*ft_get_user_input();
char	*ft_current_char(char *buf, int *i);
char	*ft_size1_char(char *line, char *chr);
char	*ft_insert_char(char *line, char chr);
char	*ft_del_char(char *line);
char	*ft_suppr_char(char *line);
void	ft_size3_char(char *chr);
char	*ft_size4_char(char *line, char *chr);
void	ft_size6_char(char *chr);
void	ft_get_cursor_info(void);
void	ft_get_cursor_pos(void);
void	ft_get_term_size(void);
void	ft_move_cursor(char side, int nb);
void	ft_mv_left(void);
void	ft_mv_right(void);
int		ft_reach_next_word(void);
int		ft_reach_previous_word(void);
void	ft_crsr_newline(void);
void	ft_scroll(int nb, char opt);
char	**ft_history_init();
char	**ft_history_new();
void	ft_history(char opt);
void	ft_display_history();

void	ft_ctrl_a();
char	*ft_ctrl_d(char *line);
void	ft_ctrl_e();
char	*ft_ctrl_u(char *line);
char	*ft_ctrl_w(char *line);
char	*ft_ctrl_y(char *line);
void	ft_sighandler_winsize_change(int signum);
void	ft_sighandler_ctrl_c(int signum);
void	ft_sighandler_ctrl_z_return(int signum);
int		ft_error(char *cause, int code);
int		ft_putc(int c);
void	ft_erase_crsrline(void);
void	ft_clean_after_cursor(void);
void	ft_free_tabzero(char **tab);
void	ft_end_clean(char *end_message);

void	ft_print_t_curs(void);
void	ft_usecap(char *cap);
int		ft_termcap_test(void);
char	*ft_addchar(char *line, char *chr);
void	ft_putchar_spe(char *c);
void	chk21(void);

#endif
