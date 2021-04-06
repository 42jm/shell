/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_dfl_signals_for_sub_process.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:21:52 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/05 23:34:38 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

void	dfl_signals_for_sub_process(void)
{
	struct sigaction	action;
	int					core_signals[10];
	int					term_signals[9];
	int					ignored_signals[7];

	get_core_signals(core_signals);
	get_term_signals(term_signals);
	get_ignored_signals(ignored_signals);
	action.sa_handler = SIG_DFL;
	action.sa_flags = SA_RESTART;
	sigfillset(&(action.sa_mask));
	set_up_action_for_given_signals(core_signals, action);
	set_up_action_for_given_signals(term_signals, action);
	set_up_action_for_given_signals(ignored_signals, action);
	sigaction(SIGCONT, &action, NULL);
	sigaction(SIGCHLD, &action, NULL);
}
