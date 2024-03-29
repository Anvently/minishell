/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_make_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 08:48:33 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/02 11:25:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	is_redir(t_atom_type type)
{
	if (type == redirection_in || type == redirection_out)
		return (1);
	return (0);
}

t_atom	*find_redir(t_atom *start, t_atom *end)
{
	if (!start)
		return (NULL);
	while (start && start != end && !is_redir(start->type))
		start = start->next;
	if (!start)
		return (NULL);
	if (is_redir(start->type))
		return (start);
	else
		return (NULL);
}

int	inscribe_file(t_list **lst, t_atom *file, t_atom *file_name)
{
	t_file_rd	*pt;
	int			res;

	pt = (t_file_rd *)((*lst)->content);
	if (file->subtype == double_in)
		pt->unlink = 1;
	if (file->subtype == double_out)
		pt->append_mode = 1;
	pt->type = file->subtype - 3;
	if (file->subtype == double_in)
	{
		res = get_heredoc(file_name->content, pt);
		if (res)
			return (res);
	}
	else
		pt->path = ft_strdup(file_name->content);
	if (!pt->path)
		return (-1);
	return (0);
}

t_list	*get_files(t_atom **start, t_atom *end)
{
	t_list	*new;
	t_list	*pt;
	t_atom	*next_file;
	t_atom	*file_name;

	pt = NULL;
	while (1)
	{
		next_file = find_redir(*start, end);
		if (!next_file)
			break ;
		new = new_file_node();
		if (!new)
			return (ft_lstclear(&pt, free_t_file), NULL);
		ft_lstadd_back(&pt, new);
		file_name = skip_space(next_file->next);
		if (inscribe_file(&new, next_file, file_name))
			return (ft_lstclear(&pt, free_t_file), NULL);
		*start = remove_file_from_atom(*start, next_file);
	}
	return (pt);
}
