/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:58:46 by npirard           #+#    #+#             */
/*   Updated: 2024/01/05 11:01:04 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <errno.h>

char		*get_var_value(char *var, char **env);
int			expand_wc(char *path, char *dest);
static int	check_file_wc(t_file_rd *file);
int			check_file_meta(t_list *files, char **env);

/// @brief Look for a given variable in env and return it as a new allocated
/// string
/// @param var Name of the variable to fin (without $)
/// @param env
/// @return Allocated string. If variable isn't found, return empty string.
/// ```NULL``` if allocation error.
char	*get_var_value(char *var, char **env)
{
	char	*var_value;
	size_t	len_var;

	len_var = ft_strlen(var);
	while (*env && ft_strncmp(*env, var, len_var))
		env++;
	if (*env)
		var_value = ft_substr(*env, len_var + 1,
				ft_strlen(*env) - len_var + 1);
	else
		var_value = ft_strdup("");
	if (!var_value)
		return (alloc_error());
	return (var_value);
}

/// @brief Check if a path string contains ```*``` char and if so expand it.
/// @param path can contain 0, 1 or more ```*```.
/// @param dest All files found will be stored in ```dest``` as a list of path
/// separated with space. If no file is found ```dest``` is set to ```NULL```.
/// @return Number of files found (equivalent to the numbers of actual arguments
/// given). ```-1``` if allocation error.
int	expand_wc(char *path, char *dest)
{
	return (0);
}

/// @brief Check if given node in a t_file_rd list contain a wildcard in file's
/// path that needs to be interpreted. If so expand it.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found, if no file was found
/// or if no error occured during wildcard's expension.
/// Set errno to ```1``` if ambiguous redirect.
/// ```-1``` if allocation error (meaning a file was found but path could not be
/// retrieved)
static int	check_file_wc(t_file_rd *file)
{
	int		nbr_files;
	char	*new_path;

	if (file->interpret_wc)
	{
		nbr_files = expand_wc(file->path, new_path);
		if (nbr_files > 1)
			return (parse_error(2, file->path));
		else if (nbr_files < 0)
		{
			free(file->path);
			file->path = NULL;
			return (-1);
		}
	}
	return (0);
}

/* /// USELESS
/// @brief Check if given file contain a $ sign in its path that needs to be
/// interpreted.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
static int	check_file_var(t_file_rd *file, char **env)
{

	return (0);
} */

/// @brief Check if given node in a t_file_rd list contain meta characters to
/// interpret in file's path. If so interpret them if necessary.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
int	check_file_meta(t_list *files, char **env)
{
	t_file_rd	*file;

	while (files)
	{
		file = (t_file_rd *) files->content;
		if (check_file_wc(file))
			return (errno);
		files = files->next;
	}
	return (0);
}
