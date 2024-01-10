/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:36:55 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/10 10:51:49 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>

void	write_into_file(int fd)
{
	char	*line;
	int		nread;

	while (1)
	{
		line = ft_gnl(0);
		if (!line)
			break;
		

	}
}

char	*create_heredoc(char *LIM)
{
	static int	nfile = 0;
	int			fd;
	char		*file_name;
	char		*str;

	str = ft_itoa(i);
	if (!str)
		return (NULL);
	file_name = ft_strjoin(HEREDOC, str);
	free(str);
	if (!file_name)
		return (NULL);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		free(file_name);
		return (NULL);
	}
	write_into_file(fd);
}

int	main(void)
{

	int	y = 30;

	char	*str;
	str = int_to_string(y);
	printf("y:%s\n", str);

}
