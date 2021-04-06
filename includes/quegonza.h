/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quegonza.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 03:16:03 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/06 14:04:11 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEGONZA_H
# define QUEGONZA_H
# include "header_42sh.h"
# include "libft.h"
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <dirent.h>

# define CTRL_A	1
# define CTRL_D	4
# define CTRL_E	5
# define CTRL_U	21
# define CTRL_W	23
# define CTRL_Y	25
# define ESC	27
# define DEL	127

typedef struct s_alias
{
	char			*name;
	char			*link;
	struct s_alias	*next;
}					t_alias;

extern t_alias		*g_alias;

typedef struct s_cap
{
	char			*cd;
	char			*ce;
	char			*cm;
	char			*dc;
}					t_cap;

typedef struct s_curs
{
	int				fd[2];
	int				row;
	int				col;
	int				crsr_row;
	int				crsr_col;
	int				cursor;
	int				strlen;
	int				prompt;
	int				eof;
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

char				*ft_bad_option(char *cmd_name, char option, char *message);
int					ft_cd_options(char **argv);
int					ft_chk_dot(char *str, char *dots);
void				ft_clean_after_cursor(void);
char				*ft_clear_dot(char *str);
int					ft_count_args(int argc, char **argv);
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
char				*ft_find_filename(char *dir_name, char *bin_name);
char				*ft_first_word(char *str);
void				ft_free_alias(void);
void				ft_free_tabzero(char **tab);
char				*ft_get_alias(char *name);
int					ft_get_cap(t_cap *cap);
void				ft_get_cursor_info(void);
void				ft_get_cursor_pos(void);
char				*ft_get_options(char **argv, char *allowed);
char				*ft_get_path(char *name);
void				ft_get_term_size(void);
char				*ft_get_user_input(void);
int					ft_getrow_fromstr(int cursor);
int					ft_getcol_fromstr(int cursor);
void				ft_history(char opt);
char				**ft_history_init(void);
char				**ft_history_new(void);
t_list				*ft_ifalias(char *name);
t_list				*ft_ifbin(char *name);
t_list				*ft_ifbuiltin(char *name);
void				ft_ignore_allsig(void);
void				ft_input_init(void);
char				*ft_insert_char(char *line, char chr);
int					ft_isoneof_chr(char chr, char *chrs);
int					ft_line_validation(void);
void				ft_move_cursor(char side, int nb);
void				ft_mv_left(void);
void				ft_mv_right(void);
char				*ft_path(char *path, char *name);
void				ft_put2str_fd(char *cause, char *msg, int fd);
int					ft_putc(int c);
int					ft_reach_next_word(void);
int					ft_reach_previous_word(void);
char				*ft_replace_alias(char *str);
char				*ft_replace_ddots(char *str);
char				*ft_replace_first_word(char *res, char *str);
char				*ft_resolve_path(char *str);
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
int					ft_valid_dir(char *path, char *arg);

void				ft_print_t_curs(void);
void				ft_usecap(char *cap);
int					ft_termcap_test(void);
char				*ft_addchar(char *line, char *chr);
void				ft_putchar_spe(char *c);
void				chk21(void);

char				*ft_get_alias(char *name);

#endif
