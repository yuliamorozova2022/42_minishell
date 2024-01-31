/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:38:02 by msulc             #+#    #+#             */
/*   Updated: 2023/01/16 14:38:28 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_string;

	i = 0;
	new_string = (unsigned char *) s;
	while (i < n)
	{
		if (new_string[i] == (unsigned char)c)
			return ((void *)(new_string + i));
		i++;
	}
	return (NULL);
}
