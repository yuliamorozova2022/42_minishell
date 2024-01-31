/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:14:42 by msulc             #+#    #+#             */
/*   Updated: 2023/01/23 10:14:45 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int				ft_lenght_numb(int n);
static	char				*ft_strswap(char *str);
static	char				ft_string_filler(char *str, int n);

char	*ft_itoa(int n)
{
	char				*string;
	unsigned int		lenght;

	lenght = (ft_lenght_numb(n));
	if (n < 0 || n == 0)
		lenght++;
	string = (char *)malloc(lenght * sizeof(char));
	if (!string)
		return (NULL);
	*string = ft_string_filler(string, n);
	lenght--;
	if (n < 0)
	{
		string[lenght - 1] = '-';
		string[lenght] = '0';
	}
	string[lenght] = '\0';
	string = ft_strswap(string);
	return (string);
}

static	char	ft_string_filler(char *str, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		n = n + 1;
		n = -n;
		while (n != 0)
		{
			str[i] = (n % 10) + 48;
			i++;
			n = n / 10;
		}
		str[0] = '8';
	}
	if (n == 0)
		str[i] = '0';
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		str[i++] = (n % 10) + 48;
		n = n / 10;
	}
	return (*str);
}

static	int	ft_lenght_numb(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
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
