/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quegonza.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 03:16:03 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/23 17:00:31 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEGONZA_H
# define QUEGONZA_H
# include "shell21.h"
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

typedef struct s_cap
{
	char			*cd;
	char			*ce;
	char			*cm;
	char			*dc;
}					t_cap;

typedef struct s_curs
{
	int				fdw;
	int				fdr;
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
	char			*temp;
	char			*copy;
	char			exit;
	struct termios	s_termios;
	struct termios	s_termios_backup;
	t_cap			cap;
}					t_curs;

extern t_curs		g_info;

void				ft_clean_after_cursor(void);
void				ft_crsr_newline(void);
void				ft_ctrl_a(void);
char				*ft_ctrl_d(char *line);
void				ft_ctrl_e(void);
char				*ft_ctrl_u(char *line);
char				*ft_ctrl_w(char *line);
char				*ft_ctrl_y(char *line);
char				*ft_current_char(char *buf, int *i);
void				ft_display_history(void);
char				*ft_del_char(char *line);
void				ft_end_clean(char *end_message);
int					ft_error(char *cause, int code);
void				ft_free_tabzero(char **tab);
int					ft_get_cap(t_cap *cap);
void				ft_get_cursor_info(void);
void				ft_get_cursor_pos(void);
void				ft_get_term_size(void);
char				*ft_get_user_input(void);
int					ft_getrow_fromstr(int cursor);
int					ft_getcol_fromstr(int cursor);
void				ft_history(char opt);
char				**ft_history_init(void);
char				**ft_history_new(void);
void				ft_input_init(void);
char				*ft_insert_char(char *line, char chr);
int					ft_isoneof_chr(char chr, char *chrs);
int					ft_line_validation(void);
void				ft_move_cursor(char side, int nb);
void				ft_mv_left(void);
void				ft_mv_right(void);
int					ft_putc(int c);
int					ft_reach_next_word(void);
int					ft_reach_previous_word(void);
void				ft_scroll(int nb, char opt);
void				ft_sighandler_winsize_change(int signum);
void				ft_sighandler_ctrl_c(int signum);
void				ft_sighandler_ctrl_z_return(int signum);
char				*ft_size1_char(char *line, char *chr);
char				*ft_size2_char(char *line, char *chr);
void				ft_size3_char(char *chr);
char				*ft_size4_char(char *line, char *chr);
void				ft_size6_char(char *chr);
int					ft_start_up(void);
int					ft_stdin_init(void);
char				*ft_suppr_char(char *line);
int					ft_termcap_init(void);
int					ft_valid_quotes(void);

void				ft_print_t_curs(void);
void				ft_usecap(char *cap);
int					ft_termcap_test(void);
char				*ft_addchar(char *line, char *chr);
void				ft_putchar_spe(char *c);
void				chk21(void);

#endif
