/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:13:03 by msulc             #+#    #+#             */
/*   Updated: 2023/01/19 10:13:06 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strback(char *str);
static	char	*ft_strcpy(char *dest, char *src);
static	int	ft_char_in_str(char *str, char c);
static	char	*ft_strswap(char *str);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	char	*s2;
	char	*set_2;

	s2 = ft_strdup(s1);
	if (!s2)
		return (NULL);
	set_2 = (char *)set;
	while (1)
		if (ft_char_in_str(set_2, s2[0]))
			s2 = ft_strback(s2);
	else
		break ;
	s2 = ft_strswap(s2);
	while (1)
		if (ft_char_in_str(set_2, s2[0]))
			s2 = ft_strback(s2);
	else
		break ;
	s2 = ft_strswap(s2);
	dest = (char *)malloc((ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s2);
	return (dest);
}

static	char	*ft_strback(char *str)
{
	int		i;
	int		j;
	char	*dest;

	dest = str;
	i = 1;
	j = 0;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	return (dest);
}

static	char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	int	ft_char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i++])
			return (1);
	}
	return (0);
}

static	char	*ft_strswap(char *str)
{
	int		i;
	char	*dest;
	char	temp;
	int		j;

	i = ft_strlen(str) - 1;
	dest = str;
	j = 0;
	while (i > j)
	{
		temp = dest[j];
		dest[j] = dest[i];
		dest[i] = temp;
		j++;
		i--;
	}
	return (dest);
}
