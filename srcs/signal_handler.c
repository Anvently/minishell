/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:19:14 by npirard           #+#    #+#             */
/*   Updated: 2024/01/16 12:18:05 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <minishell.h>
#include <libft.h>
#include <readline/readline.h>

extern int	g_mode;

void	signal_handler(int signo)
{
	if (signo == 2)
		ctr_c_handler(signo);
	else if (signo == 3)
		ctr_h_handler(signo);
}

void	ctr_c_handler(int signo)
{
	(void)signo;
	write(1, "\n", 2);
	if (g_mode == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctr_h_handler(int signo)
{
	(void)signo;
}

int	rec_signal(void)
{
	struct sigaction	action_sa;

	ft_bzero(&action_sa, sizeof(struct sigaction));
	action_sa.sa_handler = signal_handler;
	sigaction(SIGINT, &action_sa, NULL);
	return (0);
}

