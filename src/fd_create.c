/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:28:42 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:30:18 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipes(t_data	*mini)
{
	int	i;

	i = 0;
	if (mini->nbrofcom > 1)
		mini->fd_pipes = (int *)malloc(sizeof(int) * mini->nbr_pipes * 2);
	while (i < mini->nbr_pipes * 2)
	{
		if (pipe(mini->fd_pipes + i) == -1)
			return (ft_strerror("Pipes creating", "error"), -1);
		i += 2;
	}
	return (0);
}

static void	open_infile(t_node_cmd *node, int *exit_st)
{
	*exit_st = 0;
	if (node->redir_in
		&& ft_strncmp(node->redir_in, "<<", ft_strlen("<<")) == 0)
	{
		node->in_fd = dup(STDIN_FILENO);
		if (node->in_fd == -1)
		{
			ft_strerror(strerror(errno), node->in_name);
			*exit_st = 1;
		}
	}
	else if (node->redir_in)
	{
		node->in_fd = open(node->in_name, O_RDONLY, 0666);
		if (node->in_fd == -1)
		{
			ft_strerror(strerror(errno), node->in_name);
			*exit_st = 1;
		}
	}
}

static void	open_outfile(t_node_cmd *node, int *exit_st)
{
	if (node->redir_out)
	{
		if (node->redir_out
			&& ft_strncmp(node->redir_out, ">>", ft_strlen(">>") + 1) == 0)
			node->out_fd = open(node->out_name, O_CREAT
					| O_RDWR | O_APPEND, 0666);
		else
			node->out_fd = open(node->out_name, O_CREAT
					| O_RDWR | O_TRUNC, 0666);
	}
	if (node->out_fd == -1)
	{
		ft_strerror(strerror(errno), node->in_name);
		*exit_st = 1;
	}
	*exit_st = 0;
}

void	open_redirs(t_data *mini)
{
	t_node_cmd	*tmp;

	tmp = mini->cmds;
	while (tmp)
	{
		open_outfile(tmp, &mini->exitstatus);
		open_infile(tmp, &mini->exitstatus);
		tmp = tmp->next;
	}
}
