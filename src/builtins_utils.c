/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/14 16:16:37 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_env_var_and_repl(t_node **head, t_node_cmd *cmd)
{
	t_node	*cur;
	char	*tmp;

	cur = *head;
	tmp = ft_separate_key(cmd->cmd[1]);
	while (cur)
	{
		if (ft_strncmp(cur->key, tmp, ft_strlen(tmp) + 1) == 0)
		{
			free(cur->value);
			cur->value = ft_separate_value(cmd->cmd[1]);
			free(tmp);
			return (TRUE);
		}
		cur = cur->next;
	}
	free(tmp);
	return (FALSE);
}

void	ft_update_cwd(t_data *mini, char *cwd, char *pcwd)
{
	t_node	*current;

	current = mini->enviro;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PWD", 4) == 0)
		{
			free(current->value);
			current->value = ft_strdup(cwd);
		}
		if (ft_strncmp(current->key, "OLDPWD", 7) == 0)
		{
			free(current->value);
			current->value = ft_strdup(pcwd);
		}
		current = current->next;
	}
}

char	*get_arg_cd_ext(char *home, char *pcwd, t_node_cmd *cmd, char c)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	res = NULL;
	if (c == '.')
		res = dot_ext(pcwd, cmd);
	else
	{
		if (ft_strlen(cmd->cmd[1]) == 1)
			return (ft_strdup(home));
		if (cmd->cmd[1][1] == '/')
			res = ft_strjoin(home, cmd->cmd[1] + 1);
		else
		{
			tmp = ft_strjoin(home, "/");
			res = ft_strjoin(tmp, cmd->cmd[1]);
			free(tmp);
		}
	}
	return (res);
}

char	*get_arg_cd(t_node_cmd *cmd, char *home, char *old_cwd, char *pcwd)
{
	char	*res;

	res = NULL;
	if (cmd->cmd[1] == NULL)
	{
		if (home == NULL)
			return (res);
		res = ft_strdup(home);
	}
	else if (cmd->cmd[1] && ft_strncmp(cmd->cmd[1], "-", 2) == 0)
		return (ft_strdup(old_cwd));
	else if (cmd->cmd[1] && (cmd->cmd[1][0] == '~' || cmd->cmd[1][0] == '.'))
		res = get_arg_cd_ext(home, pcwd, cmd, cmd->cmd[1][0]);
	else
		res = ft_strdup(cmd->cmd[1]);
	return (res);
}

int	ft_isnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
