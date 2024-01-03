/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:35:10 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/03 15:46:43 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

int	check_between(char *str, char a, char b)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (str[i] && str[i] != a)
	{
		if (str[i] == b)
			count++;
		i++;
	}
	if (count % 2 > 0)
		return (-1);
	if (str[i] == 0)
		return (-1);
	return (i);
}
/// @brief check if there is no quote errors
/// @param str the chain to check
/// @return -1 is there's an error and a positive or null value if the string is valid
int	quote_check(char *str)
{
	int	i;
	int	res;

	i = 0;
	while (str[i])
	{
		res = 0;
		if (str[i] == 34)
			res = check_between(str + i, 34, 39);
		if (str[i] == 39)
			res = check_between(str + i, 39, 34);
		if (res < 0)
			break;
		i += res + 1;
	}
	return (res);
}

