/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/14 16:18:31 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_execute_builtin(t_data *mini, t_node_cmd *cmd)
{
	int	res;

	res = 0;
	if (cmd->in_fd > 0)
		close(cmd->in_fd);
	if (cmd->out_fd > 0)
		close(cmd->out_fd);
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		res = ft_cd(mini, cmd);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		res = ft_export(mini, cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		res = ft_unset(mini, cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		res = ft_exit(mini, cmd);
	return (res);
}

char	*dot_ext(char *pcwd, t_node_cmd *cmd)
{
	char	*path[2];
	char	*tmp;

	path[0] = NULL;
	path[1] = NULL;
	tmp = pcwd;
	if (!ft_strncmp(cmd->cmd[1], ".", 2) || !ft_strncmp(cmd->cmd[1], "./", 3))
		return (ft_strdup(pcwd));
	else if (ft_strncmp(cmd->cmd[1], "..", 3) == 0
		|| ft_strncmp(cmd->cmd[1], "../", 4) == 0)
		return (ft_substr(pcwd, 0, ft_strrchr(pcwd, '/') - pcwd));
	path[0] = ft_strdup(pcwd);
	while (ft_strncmp(cmd->cmd[1], "../", 3) == 0)
	{
		path[1] = ft_substr(path[0], 0, ft_strrchr(path[0], '/') - path[0]);
		free(path[0]);
		path[0] = path[1];
		tmp = ft_substr(cmd->cmd[1], 3, ft_strlen(cmd->cmd[1]) - 3);
		free(cmd->cmd[1]);
		cmd->cmd[1] = tmp;
	}
	path[1] = ft_strjoin(path[0], "/");
	free(path[0]);
	tmp = ft_strjoin(path[1], cmd->cmd[1]);
	return (free(path[1]), tmp);
}
