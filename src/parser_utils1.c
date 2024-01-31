/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parse_env_ext(int ex_stat, char **args, int *i)
{
	char	*tmp;

	tmp = ft_itoa(ex_stat);
	args[*i] = ft_strdup(tmp);
	free(tmp);
}

void	parse_env(t_elem **elem, char **args, int *i, t_data *mini)
{
	char	*tmp;

	if (ft_strncmp((*elem)->content, "$?", ft_strlen("$?")) == 0)
		parse_env_ext(mini->exitstatus, args, i);
	else
	{
		tmp = get_env(mini->enviro, (*elem)->content + 1);
		if (tmp == NULL)
		{
			args[*i] = ft_strdup((*elem)->content);
			if ((*elem)->next && (*elem)->next->type == WORD)
			{
				tmp = args[*i];
				args[*i] = ft_strjoin(tmp, (*elem)->next->content);
				free(tmp);
				(*elem) = (*elem)->next;
			}
		}
		else
			args[*i] = tmp;
	}
	if (args[*i])
		(*i)++;
	(*elem) = (*elem)->next;
}

static char	*parse_quot_ext_ext(t_elem **node, char **val, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (*val)
	{
		tmp = ft_strjoin(*line, *val);
		free(*val);
		*val = NULL;
	}
	else
	{
		*val = ft_strjoin(*line, (*node)->content);
		if ((*node)->next && (*node)->next->type == WORD)
		{
			tmp = ft_strjoin(*val, (*node)->next->content);
			free(*val);
			*val = NULL;
			(*node) = (*node)->next;
		}
	}
	return (tmp);
}

static void	parse_quot_ext(t_elem **node, char **val, char **line, t_data *mini)
{
	char	*tmp;

	tmp = NULL;
	if ((*node)->type == ENV && (*node)->state == IN_DQUOTE)
	{
		if (ft_strncmp((*node)->content, "$?", ft_strlen("$?")) == 0)
			*val = ft_itoa(mini->exitstatus);
		else
			*val = get_env(mini->enviro, (*node)->content + 1);
		tmp = parse_quot_ext_ext(node, val, line);
	}
	else
		tmp = ft_strjoin(*line, (*node)->content);
	free(*line);
	*line = tmp;
}

char	*parse_quo(char *line, t_elem **node, enum e_token type, t_data *mini)
{
	char	*val;

	val = NULL;
	*node = (*node)->next;
	if ((*node) && (*node)->type == type)
	{
		if (!line)
			line = ft_strdup("");
		*node = (*node)->next;
		return (line);
	}
	while ((*node) && (*node)->type != type)
	{
		if (!line)
			line = ft_strdup("");
		parse_quot_ext(node, &val, &line, mini);
		*node = (*node)->next;
	}
	if (val)
		free(val);
	if (*node)
		*node = (*node)->next;
	return (line);
}
