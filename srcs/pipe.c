/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:17:15 by npirard           #+#    #+#             */
/*   Updated: 2024/01/03 16:54:59 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static int	handle_file_in();
static int	handle_file_out();
static int	handle_redirection();
static int	handle_command(t_command command, int *fd, int *od_fd, char **env)
{
	return (0);
}

/// @brief
/// @param commands
/// @param env
/// @param old_fd
/// @return
int	exec_pipe(t_list *commands, char **env, int *old_fd)
{
	int		status;
	int		id;
	int		fd[2];


	id = fork ();
	return (status);
}
