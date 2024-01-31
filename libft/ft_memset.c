/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:21:49 by msulc             #+#    #+#             */
/*   Updated: 2023/01/11 10:21:51 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_str;

	i = 0;
	new_str = (unsigned char *) str;
	while (i < n)
	{
		new_str[i] = c;
		i++;
	}
	return (new_str);
}
