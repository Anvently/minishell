/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:17:15 by npirard           #+#    #+#             */
/*   Updated: 2024/01/19 11:03:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <fcntl.h>

static int	redirection_in(t_file_rd *file);
static int	redirection_out(t_file_rd *file);
static int	redirect_files(t_list *files, int *old_fd, t_data *data);
int			handle_redirection(t_list *files, int *old_fd,
				int *fd, t_data *data);

/// @brief
/// @param file t_file_rd struct
/// @param old_fd File descripors of input pipe. ```NULL``` for first command.
/// @return ```0``` if no error. Else ```errno```.
static int	redirection_in(t_file_rd *file)
{
	if (file_redirect(file->path, STDIN_FILENO, O_RDONLY))
		return (errno);
	if (file->type == 1 && unlink(file->path) < 0)
		return (error(errno, file->path));
	return (0);
}

/// @brief
/// @param file t_file_rd struct
/// @param fd File descripors of output pipe. ```NULL``` for last command.
/// @return ```0``` if no error. Else ```errno```.
static int	redirection_out(t_file_rd *file)
{
	int			o_flag;

	o_flag = O_RDWR | O_TRUNC | O_CREAT;
	if (file->type == 3)
		o_flag = O_APPEND | O_RDWR | O_CREAT;
	if (file_redirect(file->path, STDOUT_FILENO, o_flag))
		return (errno);
	return (0);
}

/// @brief Handle file and pipe redirection
/// @param files List of file redirection
/// @param old_fd File descripors of input pipe. ```NULL``` for first command.
/// @param data
/// @return ```0``` for success. ```errno``` if error.
static int	redirect_files(t_list *files, int *old_fd, t_data *data)
{
	t_file_rd	*file;

	while (files && !errno)
	{
		file = (t_file_rd *) files->content;
		if (check_file_meta(file, data))
			return (errno);
		if (file->type <= 1)
		{
			if (old_fd && clear_pipe(1, 0)
				&& dup2(data->stdin_copy, STDIN_FILENO) < 0)
				return (errno);
			old_fd = NULL;
			if (redirection_in(file))
				break ;
		}
		else if (file->type >= 2 && redirection_out(file))
		{
			if (old_fd)
				clear_pipe(0, 0);
			break ;
		}
		files = files->next;
	}
	return (0);
}

/// @brief Handle file and pipe redirection
/// @param files List of file redirection
/// @param old_fd File descripors of input pipe. ```NULL``` for first command.
/// @param fd File descripors of output pipe. ```NULL``` for last command.
/// @param data
/// @return ```0``` for success. ```errno``` if error.
int	handle_redirection(t_list *files, int *old_fd, int *fd, t_data *data)
{
	if (old_fd && dup_and_close(old_fd[0], STDIN_FILENO))
		return (error(errno, NULL));
	if (fd && (pipe(fd) < 0 || dup_and_close(fd[1], STDOUT_FILENO)))
		return (error(errno, NULL));
	if (redirect_files(files, old_fd, data))
		return (errno);
	return (errno);
}
