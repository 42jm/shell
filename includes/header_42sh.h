/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_42sh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:39:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/03/30 20:31:55 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_42SH_H
# define HEADER_42SH_H

# include "libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>

# define MAX_INPUT_LENGTH 1025

extern char				**g_lines;
extern t_list			*g_envlst;

typedef struct s_astnode
{
	char				*op;
	void				*content;
	struct s_astnode	*next;
}						t_astnode;

typedef struct s_envvar
{
	bool				exportable;
	char				*name;
	char				*value;
}						t_envvar;

void			sighandle_int(int signum);
void			sighandle_tstp(int signum);
void			sighandle_chld(int signum);

int				put_error(char *message, char *arg);
int				put_error_ret(char *message, char *arg, int ret);
int				put_prompt(int fd);
void			put_astlexed(t_astnode *node);
void			put_astparsed(t_astnode *node, size_t tabs);

size_t			ft_strclen_unquoted(char *s, char chr, char *quotes);
size_t			ft_stralen_unquoted(char *s, char *chars);
char			**ft_strcsplit_all(char *s, char c);
int				read_userinput(char ***input);
int				format_input(char *in, char ***input);
char			*read_all(int fd);
size_t			bashvar_len(char *str);
size_t			bashvar_len_until_next_var(char *str);
int				expand_tilde(t_astnode *node);
int				expand_param(t_astnode *node);
int				expand_words(t_astnode **ahead);
int				expand_op(t_astnode **at, t_astnode *node);
int				remove_empty_field(t_astnode *p, t_astnode **n, t_astnode **h);
char			*remove_quotes(char *str);
char			*parse_quotes(char *line);
size_t			quotationlen(char *s, char *quotes);
size_t			expansionlen(char *s);
size_t			parenlen(char *s);
t_astnode		*token_new(char *type);
int				token_delimit(t_astnode *token, char *input, size_t len);
int				handle_andor(t_astnode **at, t_astnode *prev, t_astnode *head);
int				ast_parser(t_astnode **aroot);
int				parse_curly_braces(t_astnode **aroot);
int				parse_all_parentheses(t_astnode *head);
int				ast_lexer(char *input, t_astnode **anode);
int				ast_execute(t_astnode **aroot);

size_t			astlex_oplen(char *ptr);

int				ast_localredir(t_astnode **at, int dest, int src);
int				ast_localclose(t_astnode **at, int fd);
int				astredir_simple(t_astnode **at, int fd, char *op, char *path);
int				astredir_aggregate(t_astnode **at, int fd, char *op, char *w);
int				astredir_heredoc(t_astnode **at, int fd, char *op, char *word);

int				astexec_args(t_astnode *node);
int				astexec_assign(t_astnode *node);
int				astexec_simplecmd(t_astnode **anode);
int				astexec_redir(t_astnode **ahead);
int				astexec_andor(t_astnode **ahead);
int				astexec_semicol(t_astnode **at);
int				astexec_amper(t_astnode **at);
int				astexec_pipe(t_astnode **at);
int				astexec_curly(t_astnode **at);
int				astexec_paren(t_astnode **at);

char			**ast_to_strarr(t_astnode *node);

void			free_node(t_astnode *node);
void			free_ast(t_astnode *node);
void			free_lex(t_astnode *node);

int				test_file_validity(char *path);
int				test_file_existance(char *command, char **envp, char **apath);
int				get_command_path(char *command, char **envp, char **apath);
int				execute(char **args);
int				execute_all_lines(char **lines);
int				exec_str_in_subshell(char *in, char **aout);
int				prompt_loop(void);

t_list			*env_getentry(char *varname);
t_envvar		*env_getvar(char *varname);
char			*env_getvalue(char *varname);
int				env_init(int argc, char **argv, char **envp);
t_list			*env_new(char *name, char *value, bool exportable);
int				env_set(char *varname, char *valnew, bool exportable);
int				env_unset(char *varname);
int				env_put(bool exportonly);
int				envput_export(void);
void			env_free(t_list *entry);
t_list			*env_splitnew(char *str, bool exportable);
t_list			*env_strarr_to_struct(char **envp);
char			**env_struct_to_strarr(t_list *entry);
int				env_lastret_set(int val);

int				builtin_alias(int argc, char **argv);
int				builtin_unalias(int argc, char **argv);
int				builtin_cd(int argc, char **argv);
int				builtin_echo(int argc, char **argv);
int				builtin_exit(int argc, char **argv);
int				builtin_set(int argc, char **argv);
int				builtin_unset(int argc, char **argv);
int				builtin_export(int argc, char **argv);
int				builtin_env(int argc, char **argv);
int				builtin_pwd(int argc, char **argv);
int				builtin_setenv(int argc, char **argv);
int				builtin_unsetenv(int argc, char **argv);

int				sh_neg(int nb);
char			*sig_int2str(int sig);
#endif
