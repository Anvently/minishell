/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/02 14:16:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <minishell.h>
#include <string.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>

static void	catch_signal(int signo)
{
	printf("SIGNAL CATCHED : %d\n", signo);
}

int	main(void)
{
	char	*line;

	signal(10, catch_signal);
	while ((line = readline("")))
	{
		if (!ft_strcmp(line, "PING"))
			raise(10);
		free(line);
	}
	return (0);
}

/*
int	main(void)
{
	int		fd;
	char	*line;
	char	*path;

	while ((path = readline("")))
		free(path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error(errno, path);
	while ((line = ft_gnl(fd)))
		ft_putstr_fd(line, 1);
	free(line);
	free(path);
	return (0);
} */
