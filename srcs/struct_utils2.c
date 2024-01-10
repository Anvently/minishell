/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:50 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/08 16:39:35 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

t_list	*new_cmd_node(void)
{
	t_list		*new;
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd = init_t_command(cmd);
	if (!cmd)
		return (NULL);
	new = ft_lstnew(cmd);
	if (!cmd)
	{
		free_t_command(cmd);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
void	free_t_pipe(void *tpip)
{
	t_pipe	*pip;

	if (!tpip)
		return ;
	pip = (t_pipe *)tpip;
	ft_lstclear(&pip->commands, free_t_command);
	free(pip);
}
t_pipe	*init_t_pipe(t_pipe *pip)
{
	t_list	*commands;

	if (!pip)
		return (NULL);
	commands = new_cmd_node();
	if (!commands)
	{
		free(pip);
		return (NULL);
	}
	pip->commands = commands;
	pip->condition = 0;
	return (pip);
}
t_list	*new_pipe_node(void)
{
	t_pipe	*pip;
	t_list	*new;

	pip = malloc(sizeof(t_pipe));
	if (!pip)
		return (NULL);
	pip = init_t_pipe(pip);
	if (!pip)
		return (NULL);
	new = ft_lstnew(pip);
	if  (!new)
	{
		free_t_pipe(pip);
		return (NULL);
	}
	new->content = (void *)pip;
	new->next = NULL;
	return (new);
}
