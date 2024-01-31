/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:57:51 by msulc             #+#    #+#             */
/*   Updated: 2023/01/16 15:57:58 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*fir_str;
	unsigned char	*sec_str;

	if (n == 0)
		return (0);
	fir_str = (unsigned char *) s1;
	sec_str = (unsigned char *) s2;
	i = 0;
	while ((i + 1) < n && fir_str[i] == sec_str[i])
	{
		i++;
	}
	return (fir_str[i] - sec_str[i]);
}
