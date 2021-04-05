/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_42sh.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:30:38 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/05 17:02:59 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_42SH_H
# define SIGNALS_42SH_H

# include "header_42sh.h"

void	sighandle_chld(int signum);
void	ft_sighandler_ctrl_c(int signum);
void	ft_sighandler_ctrl_z_return(int signum);
void	ft_sighandler_winsize_change(int signum);

void	get_core_signals(int *core_process_signals);
void	get_ignored_signals(int *ignored_signals);
void	get_term_signals(int *term_process_signals);
void	set_up_action_for_given_signals(int *signals, struct sigaction *action);

void	set_up_shell_signals(void);
#endif
