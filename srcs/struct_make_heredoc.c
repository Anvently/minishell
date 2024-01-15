/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_make_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:05:11 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/15 14:02:36 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

int	heredoc_warning(char *limiter, int fd)
{
	static char	*str = "minishell: warning: here-doc delimited by end-of-file (wanted `";

	close (fd);
	write (2, str, ft_strlen(str));
	write (2, limiter, ft_strlen(limiter));
	write(2, "')\n", 3);
	return (0);
}

int	inscribe_heredoc(char *file, char *limiter)
{
	int		fd;
	char	*line;

	/*penser a changer la variable globale ?*/
	fd = open(file, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		return (fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (heredoc_warning(limiter, fd));
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close (fd);
	return (0);
}

char	*get_heredoc(char *limiter)
{
	static int	count = 0;
	char		*count_to_char;
	char		*file;

	count_to_char = ft_itoa(count);
	if (!count_to_char)
		return (NULL);
	file = ft_strjoin(HEREPATH, count_to_char);
	free (count_to_char);
	if (!file)
		return (NULL);
	if (inscribe_heredoc(file, limiter))
	{
		free(file);
		return(NULL);
	}
	count++;
	return (file);
}

