/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:19:14 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 09:25:03 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <minishell.h>
#include <libft.h>
#include <readline/readline.h>

extern int	g_mode;

static void	heredoc_handler(int sig);
static void	sigint_handler(int signo);
static void	signal_handler(int signo);
int			rec_signal(void);
int			rec_heredoc_signal(void);

static void	heredoc_handler(int sig)
{
	(void)sig;
	g_mode = 1;
	write(1, "^C", 2);
	close (STDIN_FILENO);
}

static void	sigint_handler(int signo)
{
	(void)signo;
	if (g_mode == 0)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

static void	signal_handler(int signo)
{
	if (signo == 2 && g_mode == 0)
		sigint_handler(signo);
	else if (signo == 2 && g_mode == 1)
		write(1, "\n", 1);
	else if (signo == 3 && g_mode == 1)
		ft_putendl_fd("Quit (core dumped)", 1);
}

int	rec_signal(void)
{
	struct sigaction	action_sa;

	ft_bzero(&action_sa, sizeof(struct sigaction));
	rl_catch_signals = 0;
	if (g_mode == 0)
	{
		action_sa.sa_handler = signal_handler;
		action_sa.sa_flags = SA_SIGINFO | SA_RESTART;
	}
	else
		action_sa.sa_handler = SIG_IGN;
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
