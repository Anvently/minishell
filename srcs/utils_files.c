/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:27:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/19 17:26:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <fcntl.h>

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
	return (0);
}

/// @brief Read the given pipe end and does nothing with it. Used to clear
/// the buffer and to avoid memory leaks.
/// @param fd
/// @return ```err```
int	clear_pipe(int err, int fd)
{
	int		old_errno;
	char	buffer[100];

	old_errno = errno;
	while (read(fd, buffer, 100) > 0)
		continue ;
	close(fd);
	errno = old_errno;
	return (err);
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

/// @brief Open a file and redirect its to fd_out. File is ALWAYS closed.
/// @param path can be either relative or absolute.
/// @param fd_out
/// @param mode ```0``` RD_ONLY || ```1``` O_TRUNC || ```2``` O_APPEND
/// @return ```0``` on success. ```errno``` on failure. Error is printed.
int	file_redirect(char *path, int fd_out, int o_flag)
{
	int	file_fd;

	file_fd = open(path, o_flag, 0644);
	if (file_fd < 0)
		return (error(errno, path));
	if (dup_and_close(file_fd, fd_out))
		return (error(errno, path));
	return (0);
}

int	restore_std(t_data *data)
{
	if (dup2(data->stdout_copy, STDOUT_FILENO) < 0)
		return (errno);
	if (dup2(data->stdin_copy, STDIN_FILENO) < 0)
		return (errno);
	return (0);
}
