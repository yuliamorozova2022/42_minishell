/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:31:09 by msulc             #+#    #+#             */
/*   Updated: 2023/01/12 15:31:13 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	i;
	unsigned int	j;

	if (dst)
		dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	j = 0;
	if (size <= 0)
		return (src_len);
	i = ft_strlen(dst);
	i = dst_len;
	while ((i + 1) < size && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (size >= (dst_len))
		return (dst_len + src_len);
	return (src_len + dst_len - (dst_len - size));
}
