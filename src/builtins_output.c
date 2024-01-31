/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin_with_output(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "pwd", 4) == 0
		|| ft_strncmp(str, "env", 4) == 0)
		return (TRUE);
	return (FALSE);
}

void	ft_execute_fork_builtin(t_data *mini, t_node_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		ft_pwd(cmd);
	else
		ft_env(mini);
	exit(0);
}

void	ft_env(t_data *mini)
{
	t_node	*current;

	if (mini->enviro)
	{
		current = mini->enviro;
		while (current != NULL)
		{
			if (ft_strncmp(current->key, "LINES", 6) == 0
				|| ft_strncmp(current->key, "COLUMNS", 8) == 0)
			{
				current = current->next;
				continue ;
			}
			printf("%s%c%s\n", current->key, current->eq, current->value);
			current = current->next;
		}
	}
}

void	ft_pwd(t_node_cmd *cmd)
{
	char	cwd[1024];

	(void)cmd;
	if (getcwd(cwd, 1024) != NULL)
	{
		printf("%s\n", cwd);
	}
}

int	ft_echo(t_node_cmd *cmd)
{
	int	i;
	int	no_n;

	i = 0;
	no_n = FALSE;
	if (cmd->cmd[1] == NULL)
		return (printf("\n"), 0);
	if (ft_strncmp(cmd->cmd[1], "-n", ft_strlen("-n") + 1) == 0)
	{
		no_n = TRUE;
		i++;
	}
	while (cmd->cmd[++i])
	{
		if (cmd->cmd[i] && ft_strlen(cmd->cmd[i]) == 0)
			continue ;
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[i + 1])
			printf(" ");
	}
	if (no_n == FALSE)
		printf("\n");
	return (0);
}
