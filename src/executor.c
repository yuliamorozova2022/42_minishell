/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	assign_fds_ext(t_data *mini, t_node_cmd *tmp, int *flag)
{
	if (tmp->out_fd == -3)
		tmp->out_fd = mini->fd_pipes[1];
	else
	{
		close(mini->fd_pipes[1]);
		mini->fd_pipes[1] = -2;
	}
	*flag = FALSE;
}

static void	assign_fds(t_data *mini)
{
	t_node_cmd	*tmp;
	int			first;
	int			i;

	i = 0;
	tmp = mini->cmds;
	first = TRUE;
	while (tmp)
	{
		if (first == TRUE && tmp->next)
			assign_fds_ext(mini, tmp, &first);
		else if (first == FALSE && tmp->next == NULL && tmp->in_fd == -2)
			tmp->in_fd = mini->fd_pipes[mini->nbr_pipes * 2 - 2];
		else if (first == FALSE && tmp->next)
		{
			if (tmp->in_fd == -2)
				tmp->in_fd = mini->fd_pipes[i];
			if (tmp->out_fd == -3)
				tmp->out_fd = mini->fd_pipes[i + 3];
			i += 2;
		}
		tmp = tmp->next;
	}
}

static void	ft_executor_ext_two(t_data *mini, t_node_cmd *tmp, char **envp)
{
	if (ft_is_builtin(tmp->cmd[0]) && !is_builtin_with_output(tmp->cmd[0]))
		mini->exitstatus = ft_execute_builtin(mini, tmp);
	else
		mini->exitstatus = execute_cmd(tmp, mini, envp);
	signal(SIGINT, ft_signal_handler);
}

static int	ft_executor_ext_one(t_data *mini)
{
	if (create_pipes(mini) == -1)
	{
		mini->exitstatus = 1;
		return (-1);
	}
	open_redirs(mini);
	assign_fds(mini);
	return (0);
}

void	ft_executor(t_data *mini, char **envp)
{
	t_node_cmd	*tmp;

	if (ft_executor_ext_one(mini) != 0)
		return ;
	tmp = mini->cmds;
	while (tmp)
	{
		if (!tmp->cmd[0] || (tmp->cmd[0] && tmp->in_fd == -1))
		{
			if (!tmp->cmd[0] && tmp->redir_in
				&& ft_strncmp(tmp->redir_in, "<<", ft_strlen("<<") + 1) == 0)
			{
				ft_strerror("HEREDOC error", "empty command");
				mini->exitstatus = 1;
			}
			ft_close_two_fd(&tmp->in_fd, &tmp->out_fd);
			tmp = tmp->next;
			continue ;
		}
		ft_executor_ext_two(mini, tmp, envp);
		tmp = tmp->next;
	}
	ft_close_pipes(mini);
}
/* ************************************************************************** */
