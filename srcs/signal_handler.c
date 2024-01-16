/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:19:14 by npirard           #+#    #+#             */
/*   Updated: 2024/01/16 13:41:38 by npirard          ###   ########.fr       */
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
		sigint_handler(signo);
	else if (signo == 3)
		sigquit_handler(signo);
}

void	sigint_handler(int signo)
{
	(void)signo;

	if (g_mode == 0)
	{
		write(1, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void	sigquit_handler(int signo)
{
	(void)signo;
}

int	rec_signal(void)
{
	struct sigaction	action_sa;

	ft_bzero(&action_sa, sizeof(struct sigaction));
	rl_catch_signals = 0;
	action_sa.sa_handler = signal_handler;
	sigaction(SIGINT, &action_sa, NULL);
	sigaction(SIGQUIT, &action_sa, NULL);
	return (0);
}
