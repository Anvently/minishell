/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:53:10 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/10 14:11:52 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

void	lst_display(t_list *pt, void (*disp)(void *))
{
	while (pt)
	{
		disp(pt->content);
		pt = pt->next;
	}
}

void	file_display(void *file)
{
	t_file_rd	*pt;

	pt = file;
	if (!pt)
		return ;
	printf("\n/----FILE----/\n");
	printf("path:%s\nappend:%d\nunlink:%d\n", pt->path, pt->append_mode, pt->unlink);
}

void	command_display(void *command)
{
	t_command	*pt;

	pt = command;
	if (!pt)
		return ;
	printf("\n/----COMMAND----/\n");
	printf("args:\n");
	ft_print_strs(pt->argv);
	printf("files_in:\n");
	lst_display(pt->files_in, file_display);
	printf("files_out:\n");
	lst_displat(pt->files_out, file_display);
}

void	pipe_display(void *pip)
{
	t_pipe	*pt;

	pt = pip;
	if (!pt)
		return ;
	printf("\n/----PIPE----/\n");
	printf("condition: %d", pt->condition);
	printf("command list:/n");
	lst_display(pt->commands, command_display);
}
