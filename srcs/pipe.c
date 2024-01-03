/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:17:15 by npirard           #+#    #+#             */
/*   Updated: 2024/01/03 16:37:13 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_file_in();
static int	handle_file_out();
static int	handle_redirection(t_command *pipe, );

/// @brief
/// @param pipe
/// @param env
/// @param old_fd
/// @param i_command
/// @return
int	exec_pipe(t_pipe *pipe, char **env, int *old_fd, int i_command)
{
	int		status;
	int		id;
	int		fd[2];

	id = fork ();
	if (!handle_redirection())
	return (status);
}
