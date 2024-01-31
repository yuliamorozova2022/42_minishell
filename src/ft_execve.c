/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:44:23 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:45:05 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_path(t_data	*mini, t_node_cmd *node)
{
	char	*tmp;
	int		i;
	int		res;

	res = 0;
	i = 0;
	if (node->cmd[0] == NULL || ft_strlen(node->cmd[0]) == 0)
		return (FALSE);
	while (mini->path && mini->path[i])
	{
		tmp = ft_strjoin(mini->path[i++], "/");
		node->path = ft_strjoin(tmp, node->cmd[0]);
		free(tmp);
		res = access(node->path, X_OK);
		if (res == 0)
			return (TRUE);
		free(node->path);
		node->path = NULL;
	}
	return (FALSE);
}

void	ft_execve(t_node_cmd *node, t_data *mini, char **env)
{
	if (node->path == NULL && get_path(mini, node) == FALSE)
	{
		ft_strerror("command not found", node->cmd[0]);
		ft_close_two_fd(&node->in_fd, &node->out_fd);
		exit (127);
	}
	if (execve(node->path, node->cmd, env) == -1)
	{
		ft_close_two_fd(&node->in_fd, &node->out_fd);
		ft_strerror(strerror(errno), node->cmd[0]);
		exit (126);
	}
}
