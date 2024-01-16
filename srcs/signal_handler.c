/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:19:14 by npirard           #+#    #+#             */
/*   Updated: 2024/01/16 15:43:38 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <minishell.h>
#include <libft.h>
#include <readline/readline.h>

extern int	g_mode;

void	heredoc_handler(int sig)
{
	(void)sig;
	g_mode = 1;
	write(1, "^C", 2);
	close (STDIN_FILENO);
}

void	signal_handler(int signo)
{
	if (signo == 2)
		sigint_handler(signo);
}

void	sigint_handler(int signo)
{
	(void)signo;

	if (g_mode == 0)
	{

		write(2, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
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

int	rec_heredoc_signal(void)
{
	struct sigaction	action_sa;

	ft_bzero(&action_sa, sizeof(struct sigaction));
	action_sa.sa_handler = heredoc_handler;
	sigaction(SIGINT, &action_sa, NULL);
	return (0);
}
