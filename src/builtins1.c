/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/14 16:47:15 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_unset(t_data *mini, t_node_cmd *cmd)
{
	t_node	*current;
	int		i;

	i = 0;
	if (!cmd->cmd[1])
		return (0);
	current = mini->enviro;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, cmd->cmd[1], ft_strlen(cmd->cmd[1])) == 0)
		{
			ft_remove_node(&mini->enviro, cmd->cmd[1]);
			if (mini->path != NULL)
			{
				while (mini->path[i])
					free(mini->path[i++]);
				free(mini->path);
				mini->path = NULL;
			}
			return (ft_path_filler(mini), 0);
		}
		else
			current = current->next;
	}
	return (0);
}

static int	ex_command_tester(char *comm)
{
	int	i;

	i = 0;
	if (ft_strlen(comm) <= 1)
	{
		ft_strerror(comm, "not a valid identifier");
		return (0);
	}
	if (!ft_isalpha(comm[0]) && comm[0] != 95)
	{
		ft_strerror(comm, "not a valid identifier");
		return (0);
	}
	while (comm[i])
	{
		if (comm[i] == 61)
			return (1);
		i++;
	}
	ft_strerror(comm, "not a valid identifier");
	return (0);
}

int	ft_export(t_data *mini, t_node_cmd *cmd)
{
	t_node	*cur;

	if (cmd->cmd[1])
	{
		if (!ex_command_tester(cmd->cmd[1]))
			return (2);
		if (check_env_var_and_repl(&mini->enviro, cmd) == FALSE)
			ft_add_end(&mini->enviro, cmd->cmd[1]);
		path_clean(mini);
		ft_path_filler(mini);
		return (0);
	}
	cur = mini->enviro;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, "LINES", 6) != 0
			|| ft_strncmp(cur->key, "COLUMNS", 8) != 0)
			printf("declare -x %s%c\"%s\"\n", cur->key, cur->eq, cur->value);
		cur = cur->next;
	}
	return (0);
}

int	ft_cd(t_data *mini, t_node_cmd *cmd)
{
	char	cwd[1024];
	char	pcwd[1024];
	char	*dest;

	if (cmd->cmd[1] && cmd->cmd[2] != NULL)
	{
		ft_strerror("too many arguments", cmd->cmd[0]);
		return (1);
	}
	getcwd(pcwd, 1024);
	dest = get_arg_cd(cmd, mini->home, mini->old_cwd, pcwd);
	if (chdir(dest) == -1)
	{
		ft_strerror(strerror(errno), dest);
		free(dest);
		return (1);
	}
	getcwd(cwd, 1024);
	free(mini->old_cwd);
	mini->old_cwd = ft_strdup(pcwd);
	ft_update_cwd(mini, cwd, pcwd);
	free(dest);
	return (0);
}

int	ft_exit(t_data *mini, t_node_cmd *cmd)
{
	int	res;

	res = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->cmd[1] && ft_isnum(cmd->cmd[1]) == FALSE)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		res = 2;
	}
	else if (cmd->cmd[1] && ft_isnum(cmd->cmd[1]) && cmd->cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (cmd->cmd[1] && ft_isnum(cmd->cmd[1]))
		res = ft_atoi(cmd->cmd[1]);
	ft_cleaning(mini);
	exit(res);
}
