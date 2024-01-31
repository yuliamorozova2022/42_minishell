/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:28:34 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:31:15 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close_two_fd(int *fd1, int *fd2)
{
	if (*fd1 > 0)
	{
		close(*fd1);
		*fd1 = -2;
	}
	if (*fd2 > 0)
	{
		close(*fd2);
		*fd2 = -3;
	}
}

void	ft_close_pipes(t_data *mini)
{
	int	i;

	i = 0;
	while (i < mini->nbr_pipes * 2)
	{
		ft_close_two_fd(&mini->fd_pipes[i], &mini->fd_pipes[i + 1]);
		i += 2;
	}
}
