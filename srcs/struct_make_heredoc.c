/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_make_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:05:11 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/19 12:21:30 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

extern int	g_mode;

int	heredoc_warning(char *limiter, int fd)
{
	static char	*str = "minishell: warning: here-doc delimited by end-of-file (wanted `";

	close (fd);
	write (2, str, ft_strlen(str));
	write (2, limiter, ft_strlen(limiter));
	write(2, "')\n", 3);
	return (0);
}

int	write_in_file(int fd, char *limiter)
{
	char	*line;

	rec_heredoc_signal();
	while (1)
	{
		line = readline("> ");
		if (!line && g_mode == 0)
			return (heredoc_warning(limiter, fd));
		if (g_mode == 1)
		{
			free(line);
			g_mode = 0;
			return (130);
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}
char	*get_limiter(char *str)
{
	int		len;
	char	*lim;
	int		i;

	len = ft_strlen(str) - 2;
	lim = malloc((len + 1) * sizeof(char));
	if (!lim)
		return (NULL);
	i = 0;
	while (i < len)
	{
		lim[i] = str[i + 1];
		i++;
	}
	lim[i] = 0;
	return (lim);
}


int	inscribe_heredoc(char *file, char *limiter)
{
	int		fd;
	int		fd_stdin;
	int		res;
	char	*real_limiter;

	real_limiter = limiter;
	if (limiter[0] == '\"' || limiter[0] == '\'')
	{
		real_limiter = get_limiter(limiter);
		if (!real_limiter)
			return (-1);
	}
	fd_stdin = dup(STDIN_FILENO);
	fd = open(file, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		return (-1);
	res = write_in_file(fd, real_limiter);
	close (fd);
	if (res)
		dup2(fd_stdin, STDIN_FILENO);
	close (fd_stdin);
	rec_signal();
	return (res);
}

int	get_heredoc(char *limiter, t_file_rd *pt)
{
	static int	count = 0;
	int			res;
	char		*count_to_char;
	char		*file;

	count_to_char = ft_itoa(count);
	if (!count_to_char)
		return (-1);
	file = ft_strjoin(HEREPATH, count_to_char);
	free (count_to_char);
	if (!file)
		return (-1);
	res = inscribe_heredoc(file, limiter);
	if (res)
	{
		unlink(file);
		free(file);
		pt->path = NULL;
		errno = res;
		return(res);
	}
	count++;
	pt->path = file;
	return (0);
}

