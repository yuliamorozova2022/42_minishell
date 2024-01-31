/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:35:43 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:36:40 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_strerror(char *msg, char *name)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_perror(char *msg, char *utils)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (utils)
	{
		write(STDERR_FILENO, utils, ft_strlen(utils));
		if (ft_strncmp(utils, "|", ft_strlen("|")) != 0)
			free(utils);
	}
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
