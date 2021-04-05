/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_up_shell_signals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:53:38 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/05 23:07:16 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

static void	set_up_dfl_signals(struct sigaction action)
{
	int core_signals[10];
	int	term_signals[9];

	action.sa_handler = SIG_DFL;
	get_core_signals(core_signals);
	get_term_signals(term_signals);
	set_up_action_for_given_signals(core_signals, action);
	set_up_action_for_given_signals(term_signals, action);
}

static void	set_up_ign_signals(struct sigaction action)
{
	int	ignored_signals[7];

	get_ignored_signals(ignored_signals);
	action.sa_handler = SIG_IGN;
	set_up_action_for_given_signals(ignored_signals, action);
}

void	set_up_shell_signals(void)
{
	struct sigaction	action;

	action.sa_flags = SA_RESTART;
	sigfillset(&(action.sa_mask));
	set_up_dfl_signals(action);
	set_up_ign_signals(action);
	action.sa_handler = ft_sighandler_ctrl_c;
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = sighandle_chld;
	sigaction(SIGCHLD, &action, NULL);
	action.sa_handler = ft_sighandler_winsize_change;
	sigaction(SIGWINCH, &action, NULL);
	action.sa_handler = ft_sighandler_ctrl_z_return;
	sigaction(SIGCONT, &action, NULL);
}
