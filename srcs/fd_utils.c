/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:27:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 11:45:33 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

/// @brief Write content of fd_in to fd_out.
/// @param fd_in
/// @param fd_out
/// @return ```0``` on success. ```errno``` on error.
int	fd_to_fd(int fd_in, int fd_out)
{
	char	buffer[BUFFER_SIZE];
	size_t	byte_r;

	byte_r = read(fd_in, buffer, BUFFER_SIZE);
	while (byte_r > 0)
	{
		if (write(fd_out, buffer, byte_r) < 0)
		{
			byte_r = -1;
			break ;
		}
		byte_r = read(fd_in, buffer, BUFFER_SIZE);
	}
	if (byte_r < 0)
		return (errno);
	return (0);
}

/// @brief Read the given pipe end and does nothing with it. Used to clear
/// the buffer and to avoid memory leaks.
/// @param fd
void	clear_pipe(int fd)
{
	while (read(fd, NULL, 100) > 0)
		continue ;
}

/// @brief Dup file_fd to std_fd then close it. file_fd is ALWAYS close, even
/// if dup2 fails.
/// @param file_fd
/// @param std_fd
/// @return ```0``` on success. ```errno``` on failure.
int	dup_and_close(int file_fd, int std_fd)
{
	if (dup2(file_fd, std_fd) < 0)
	{
		close(file_fd);
		return (errno);
	}
	close(file_fd);
	return (0);
}
