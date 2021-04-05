/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_get_core_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:26:02 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/02 18:44:22 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

void	get_core_signals(int *core_signals)
{
	int i;

	i = 0;
	core_signals[i++] = SIGILL;
	core_signals[i++] = SIGTRAP;
	core_signals[i++] = SIGABRT;
	core_signals[i++] = SIGFPE;
	core_signals[i++] = SIGBUS;
	core_signals[i++] = SIGSEGV;
	core_signals[i++] = SIGSYS;
	core_signals[i++] = SIGXCPU;
	core_signals[i++] = SIGXFSZ;
	core_signals[i++] = 0;
}
