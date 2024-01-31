/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:12:19 by msulc             #+#    #+#             */
/*   Updated: 2023/01/16 13:12:23 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					i;
	unsigned char		b;

	i = 0;
	b = (char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == b)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
