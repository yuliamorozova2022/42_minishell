/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:27:47 by msulc             #+#    #+#             */
/*   Updated: 2023/01/17 17:28:03 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	while_function(const char *str, int result, int i);

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	minus;

	i = 0;
	result = 0;
	minus = 1;
	while (str[i])
	{
		if (str[i] < 9 || (str[i] > 13 && str[i] < 32)
			|| (str[i] > 32 && str[i] < 43) || str[i] == 44
			|| (str[i] > 45 && str[i] < 48) || str[i] > 57
			|| ((str[i] == '-' || str[i] == '+') && (str[i + 1] < 48
					|| str[i + 1] > 57)))
			return (0);
		if (str[i] == '-')
			minus = minus * -1;
		if (str[i] >= 48 && str[i] <= 57)
		{
			result = while_function(str, result, i) * minus;
			return (result);
		}
		i++;
	}
	return (result);
}

static	int	while_function(const char *str, int result, int i)
{
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10;
		result = result + (str[i] - 48);
		i++;
	}
	return (result);
}
