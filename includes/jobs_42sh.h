/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_42sh.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:39:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/01/28 22:17:50 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_42SH_H
# define JOBS_42SH_H

# include "header_42sh.h"
# include <termios.h>

/*
** __________
** STRUCTURES
**
**		s_job
**	pgid		process group id of all processes under this job
**	tmodes		backup of the job terminal modes
**	foreground	true if in foreground, false if in background
**	command		the command string describing the job
**	status		string describing the job's state
**	nbr			indentifier used by builtins
**	notified	variable checked to see if the job is in need of a notification
*/
typedef struct s_job
{
	pid_t			pgid;
	struct termios	tmodes;
	int				foreground;
	char			*command;
	char			*status;
	int				nbr;
	int				notified;
}	t_job;

/*
**		s_shell	
**	pgid			shell process group id
**	joblst			jobs that survived their scope, ordered by last running
**	tmodes			backup of shell initial terminal modes
**	terminal		terminal fd, equivalent of initial STDIN_FILENO
**	is_subshell		starts at 0. subshells should increment it
**	is_interactive	isatty(STDIN_FILENO) at startup, set to 0 if subshell
**	job_blueprint	created jobs live here during first execution
*/
typedef struct s_shell
{
	pid_t			pgid;
	t_list			*joblst;
	struct termios	tmodes;
	int				terminal;
	int				is_subshell;
	int				is_interactive;
	t_job			*job_blueprint;
	int				exit_warning;
}	t_shell;

/*
** ________________
** GLOBAL VARIABLES
**
**	g_shell		used to implement job control
*/
extern t_shell	*g_shell;

/*
** ______________
** INITIALISATION
**
**	job_init_shell()	mallocs g_shell, ignore stop signals, sets pgid to pid
**	jobget_next_nbr()	returns highest allocated job nbr + 1
**	job_start_new()		create a new job and set it as blueprint
*/
int		job_init_shell(void);
int		jobget_next_nbr(void);
int		job_start_new(t_astnode *node);

/*
** _______
** ZA ZONE
**
**		job_blueprint.c
*/
int		job_set_current(t_job *job);
int		job_complete_blueprint(void);

/*
**		job_wait.c
*/
int		job_wait(t_job *job, int nohang);
int		exejob_wait(pid_t pid);

/*
**		job_launch.c
*/
int		job_init_process(t_job *job);
int		put_job_in_foreground(t_job *job, int cont);
int		put_job_in_background(t_job *job, int cont);

/*
** ______
** STATUS
**
**		job_notifs.c		write notif str
**	job_notify			write notif str of job or all approriate jobs if NULL
*/
int		job_notify(t_job *job, int unnotified_only, char option, int fd);

/*
**		job_puts.c			writes elements of job
**	job_put_nbr			writes "[job->nbr]X" to fd. X can be one of +, -, space
**	job_put_currents	either writes '+', '-', or ' '
**	job_put_pgid		writes "job->pgid", space filled to len 5
**	job_put_status		writes "job->status", space filled to len 23
*/
void	job_put_nbr(t_job *job, int fd);
void	job_put_currents(t_job *job, int fd);
void	job_put_pgid(t_job *job, int fd);
void	job_put_status(t_job *job, int fd);

/*
**		job_update.c		modify job status string
**	job_set_status		replace job->status str according to the status arg
**	job_update_status	wait on job without hanging. wait on all jobs if NULL
*/
int		job_set_status(t_job *job, int status);
int		job_update_status(t_job *job);

/*
** ____
** FREE
**
**		job_cleanup.c
**	job_cleanup()		free nbr job or finished jobs if nbr == 0
*/
int		job_cleanup(int nbr);

/*
**		job_free.c
**	job_free()			free job struct
*/
void	job_free(t_job *job);

/*
** _______
** FINDERS
**
**		job_gets.c			contains job finding functions
**	jobget_number()		returns job with nbr == n
**	jobget_jobid()		find job from posix job_id
**	.._nth_current()	n=0 returns current, n=1 returns previous, etc...
*/
t_job	*jobget_pgid(pid_t pgid);
t_job	*jobget_number(int n);
t_job	*jobget_jobid(char *job_id);
t_job	*jobget_nth_current(size_t n);

/*
** ________
** BUILTINS
**
**		bltn_jobs.c
**	builtin_jobs()	lists job(s)
**	builtin_fg()	puts a job in foreground
**	builtin_bg()	puts job(s) in background
*/
int		builtin_jobs(int argc, char **argv);
int		builtin_fg(int argc, char **argv);
int		builtin_bg(int argc, char **argv);

/*
** __________________
** CONVERT AST TO STR
**
**		job_ast2str.c		main file
**	job_ast2str()	calling function, wrapper for main function
**	astcmdstr()		main function, calls op dispatcher or handles word nodes
**	astcmdstr_cpy()	adds str argument to buffer, then updates buffer
*/
char	*job_ast2str(t_astnode *head);
int		astcmdstr(t_astnode *node, char **acmd);
int		astcmdstr_cpy(char **acmd, char *str);

/*
**		job_ast2str_op.c	operator handlers
**	..op_after()	put order: contents,	op,			next
**	..op_before()	put order: op,			contents,	next
**	..op_around()	put order: op_left,		contents,	op_right,	next
**	..op_ignore()	put order: contents,	next
**	..op_heredoc()	put order: op,			next,		heredoc,	word_delim
*/
int		astcmdstr_op_after(t_astnode *node, char **acmd);
int		astcmdstr_op_before(t_astnode *node, char **acmd);
int		astcmdstr_op_around(t_astnode *node, char **acmd);
int		astcmdstr_op_ignore(t_astnode *node, char **acmd);
int		astcmdstr_op_heredoc(t_astnode *node, char **acmd);

/*
**		job_ast2str_get.c	helpers for operator handlers
**	..braces()		op_around helper: return relevent op_left and op_right
*/
void	oparound_get_braces(char *op, char **left, char **right);

#endif
