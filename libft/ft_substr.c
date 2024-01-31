/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:01:32 by msulc             #+#    #+#             */
/*   Updated: 2023/01/18 15:02:40 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*dst;

	i = ft_strlen(s);
	if (start >= i || len == 0)
		return (ft_strdup(""));
	j = len;
	if ((len + start) > i)
		j = i - start;
	dst = (char *)malloc((j + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	j = 0;
	while (s[start] && j < len)
	{
		dst[j] = s[start];
		j++;
		start++;
	}
	dst[j] = '\0';
	return (dst);
}
