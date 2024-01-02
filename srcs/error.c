/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:35 by npirard           #+#    #+#             */
/*   Updated: 2024/01/02 12:19:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>

int	error(int err, char *str)
{
	ft_putstr_fd(strerror(err), 2);
	if (str)
	{
		write(2, ": ", 2);
		ft_putstr_fd(str, 2);
	}
	write(2, "\n", 1);
	return (err);
}
