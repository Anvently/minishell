/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:06:57 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/10 17:10:51 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

void	free_t_file(void *file)
{
	t_file_rd	*pt;

	pt = (t_file_rd *)file;

	if (!pt)
		return ;
	if (pt->path)
		free(pt->path);
	free(pt);
}

void	init_t_file(t_file_rd *file)
{
	if (!file)
		return ;
	file->path = NULL;
	file->unlink = 0;
	file->append_mode = 0;
}

t_list	*new_file_node(void)
{
	t_list		*new;
	t_file_rd	*file;

	file = malloc(sizeof(t_file_rd));
	if (!file)
		return (NULL);
	init_t_file(file);
	new = ft_lstnew(file);
	if (!new)
	{
		free_t_file(file);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	free_t_command(void *comd)
{
	t_command *cmd;

	cmd = (t_command *)comd;
	if (!cmd)
		return ;
	if (cmd->argv)
		free(cmd->argv);
	if (cmd->files_in)
		ft_lstclear(&cmd->files_in, free_t_file);
	if (cmd->files_out)
		ft_lstclear(&cmd->files_out, free_t_file);
	free(cmd);
}

t_command	*init_t_command(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->files_in = NULL;
	// if (!cmd->files_in)
	// {
	// 	free(cmd);
	// 	return (NULL);
	// }
	cmd->files_out = NULL;
	// if (!cmd->files_out)
	// {
	// 	free_t_file(cmd->files_in);
	// 	free(cmd);
	// 	return (NULL);
	// }
	return (cmd);
}
