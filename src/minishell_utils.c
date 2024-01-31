/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_data_init(t_data *mini, char **envp)
{
	char	*tmp;

	mini->line = NULL;
	mini->cmds = NULL;
	mini->nbrofcom = 0;
	mini->nbr_pipes = 0;
	mini->fd_pipes = NULL;
	mini->lex = NULL;
	mini->enviro = create_env_list(envp);
	tmp = getenv("USER");
	if (tmp != NULL)
		mini->prompt = ft_strjoin(tmp, ".minishell ~> ");
	else
		mini->prompt = ft_strjoin("beautiful", ".minishell ~> ");
	mini->exitstatus = 0;
	tmp = getenv("PWD");
	if (tmp != NULL)
		mini->old_cwd = ft_strdup(tmp);
	else
		mini->old_cwd = ft_strdup(getenv("HOME"));
	mini->home = ft_strdup(getenv("HOME"));
	ft_path_filler(mini);
}

void	ft_reset_values(t_data *mini)
{
	if (mini->cmds)
		remove_cmd_list(&mini->cmds);
	if (mini->lex)
		free_list(mini->lex);
	mini->nbrofcom = 0;
	mini->nbr_pipes = 0;
	if (mini->fd_pipes)
		free(mini->fd_pipes);
	if (mini->line)
		free(mini->line);
	mini->fd_pipes = NULL;
	mini->lex = NULL;
	mini->cmds = NULL;
}

void	ft_path_filler(t_data *mini)
{
	t_node	*current;

	current = mini->enviro;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PATH", 5) == 0)
		{
			mini->path = ft_split(current->value, ':');
			return ;
		}
		current = current->next;
	}
	mini->path = NULL;
	return ;
}

int	ft_has_characters(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] > 32)
				return (1);
			i++;
		}
	}
	return (0);
}
