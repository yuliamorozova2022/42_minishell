/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:41:59 by msulc             #+#    #+#             */
/*   Updated: 2023/01/20 10:42:04 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_wn(char const *s, char c);
static	char	*ft_new_str_fill(char *strings, char const *s, char c, int i);
static	int	ft_sec_len(char const *s, int i, char c);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**strings;

	j = ft_wn(s, c);
	strings = (char **)malloc((j + 1) * sizeof(char *));
	if (!strings || j == '0')
		return (NULL);
	strings[j] = 0;
	i = 0;
	k = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			k = ft_sec_len(s, i, c);
			strings[j] = (char *)malloc(sizeof(char) * k);
			strings[j] = ft_new_str_fill(strings[j], s, c, i);
			j++;
		}
		i++;
	}
	return (strings);
}

static	int	ft_wn(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

static	char	*ft_new_str_fill(char *strings, char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		strings[j] = s[i];
		j++;
		i++;
	}
	strings[j] = '\0';
	return (strings);
}

static	int	ft_sec_len(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		j++;
		i++;
	}
	return (j + 1);
}
