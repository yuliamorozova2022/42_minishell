/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:22:03 by msulc             #+#    #+#             */
/*   Updated: 2023/01/17 10:22:08 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lenght;

	if (!big && len == 0)
		return (0);
	lenght = 0;
	while (little[lenght])
		lenght++;
	if (lenght == 0 || big == little)
		return ((char *)big);
	j = 0;
	while (big[j] && j <= len)
	{
		i = 0;
		if (big[j] == little[i])
		{
			while (big[j++] == little[i++] && j <= len)
				if (little[i] == '\0')
					return ((char *)big + (j - lenght));
			j = j - i;
		}
		j++;
	}
	return (0);
}
