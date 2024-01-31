/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:46:39 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:54:22 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_waitpid(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 1)
		return (WEXITSTATUS(status));
	return (130);
}

int	heredoc_function(t_node_cmd *node)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (ft_strerror(strerror(errno), "heredoc pipe"), -1);
	else
	{
		while (1)
		{
			line = readline("heredoc> ");
			if (line == NULL || (ft_strncmp(line, node->in_name,
						ft_strlen(node->in_name) + 1) == 0))
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		if (line)
			free(line);
		ft_close_two_fd(&fd[1], &node->in_fd);
		node->in_fd = fd[0];
	}
	return (0);
}

static int	execute_cmd_ext(t_node_cmd *node, int is_builtin)
{
	if (node->in_fd < 0)
		node->in_fd = dup(STDIN_FILENO);
	if (node->out_fd < 0)
		node->out_fd = dup(STDOUT_FILENO);
	if (node->redir_in
		&& ft_strncmp(node->redir_in, "<<", ft_strlen("<<") + 1) == 0)
		heredoc_function(node);
	if (is_builtin == FALSE)
	{
		if (dup2(node->in_fd, STDIN_FILENO) < 0)
			return (ft_strerror(strerror(errno), "dup2 error"), -2);
	}
	else
	{
		if (node->in_fd > 0)
			close(node->in_fd);
	}
	if (dup2(node->out_fd, STDOUT_FILENO) < 0)
		return (ft_strerror(strerror(errno), "dup2 error"), -3);
	return (0);
}

int	execute_cmd(t_node_cmd *node, t_data *mini, char **env)
{
	pid_t	pid;
	int		is_builtin;
	int		exit_status;

	is_builtin = is_builtin_with_output(node->cmd[0]);
	pid = fork();
	if (pid < 0)
		return (ft_strerror(strerror(errno), "fork"), -1);
	else if (pid == 0)
	{
		signal(SIGINT, sig_handl_child);
		if (execute_cmd_ext(node, is_builtin) != 0)
			return (-1);
		if (is_builtin)
			ft_execute_fork_builtin(mini, node);
		ft_execve(node, mini, env);
	}
	signal(SIGINT, SIG_IGN);
	ft_close_two_fd(&node->in_fd, &node->out_fd);
	exit_status = ft_waitpid(pid);
	signal(SIGINT, ft_signal_handler);
	return (exit_status);
}
