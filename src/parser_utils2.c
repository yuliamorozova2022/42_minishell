/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	count_quotes_redir_args(t_elem **elem, enum e_token type, int *i)
{
	if (type == DOUBLE_QUOTE || type == QOUTE)
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type != type)
			(*elem) = (*elem)->next;
		(*i)++;
	}
	else if (is_redir(type))
	{
		while ((*elem)->type != WORD && (*elem)->type != ENV)
			(*elem) = (*elem)->next;
		(*elem) = (*elem)->next;
	}
}

int	count_args(t_elem *elem)
{
	t_elem	*tmp;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (tmp->type == WORD || tmp->type == ENV)
			i++;
		else if (tmp->type == DOUBLE_QUOTE || tmp->type == QOUTE
			|| is_redir(tmp->type))
		{
			count_quotes_redir_args(&tmp, tmp->type, &i);
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (i);
}

int	get_pipe_nbr(t_list_n *list)
{
	int		n;
	t_elem	*tmp;

	n = 0;
	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
			n++;
		tmp = tmp->next;
	}
	return (n);
}

int	is_full(char *str)
{
	int	res;

	res = 0;
	res = access(str, F_OK);
	if (res == 0)
		return (TRUE);
	return (FALSE);
}

void	abs_path_check(t_node_cmd **head)
{
	t_node_cmd	*current;

	current = *head;
	while (current)
	{
		if (is_full(current->cmd[0]))
		{
			current->path = ft_strdup(current->cmd[0]);
			return ;
		}
		current = current->next;
	}
}
