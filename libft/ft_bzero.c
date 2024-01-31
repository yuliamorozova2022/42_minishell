/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:09:14 by msulc             #+#    #+#             */
/*   Updated: 2023/01/11 14:09:18 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*new_str;

	i = 0;
	new_str = (unsigned char *) str;
	while (i < n)
	{
		new_str[i] = 0;
		i++;
	}
}
