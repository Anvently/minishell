/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:23 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/16 14:16:30 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>
#include <signal.h>

extern int	g_mode;

void	heredoc_handler(int sig)
{
	(void)sig;
	g_mode = 1;
	write(1, "^C\n", 3);
}

int	rec_heredoc_signal(void)
{
	struct sigaction	action_sa;

	ft_bzero(&action_sa, sizeof(struct sigaction));
	action_sa.sa_handler = heredoc_handler;
	sigaction(SIGINT, &action_sa, NULL);
	return (0);
}