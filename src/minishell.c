/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/14 16:46:56 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	extern char	**environ;
	t_data		mini;

	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_data_init(&mini, environ);
	while (1)
	{
		if (ft_line(&mini) == 0)
			ft_executor(&mini, environ);
		ft_reset_values(&mini);
	}
	return (0);
}

int	ft_line(t_data *mini)
{
	mini->line = readline(mini->prompt);
	if (mini->line == NULL)
	{
		ft_cleaning(mini);
		write(STDOUT_FILENO, "exit\n", 5);
		exit (0);
	}
	if (ft_strlen(mini->line) == 0 || ft_has_characters(mini->line) == 0)
		return (1);
	add_history(mini->line);
	mini->lex = lexer(mini->line);
	if (sintax_check(mini->lex))
	{
		mini->exitstatus = 1;
		return (1);
	}
	mini->nbr_pipes = get_pipe_nbr(mini->lex);
	mini->nbrofcom = mini->nbr_pipes + 1;
	mini->cmds = parsing(mini->lex, mini);
	return (abs_path_check(&mini->cmds), 0);
}

void	ft_cleaning(t_data *mini)
{
	path_clean(mini);
	rl_clear_history();
	if (mini->line)
		free(mini->line);
	if (mini->fd_pipes)
		free(mini->fd_pipes);
	free(mini->prompt);
	remove_env_list(&mini->enviro);
	if (mini->cmds)
		remove_cmd_list(&mini->cmds);
	if (mini->lex)
		free_list(mini->lex);
	if (mini->home)
		free(mini->home);
	if (mini->old_cwd)
		free(mini->old_cwd);
}

void	path_clean(t_data *mini)
{
	int	i;

	i = -1;
	if (mini->path)
	{
		while (mini->path[++i])
			free(mini->path[i]);
		free(mini->path);
	}
}
