/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_word(t_elem **elem, char **args, int *i)
{
	args[*i] = ft_substr((*elem)->content, 0, (*elem)->len + 1);
	(*i)++;
	(*elem) = (*elem)->next;
}

char	*get_name(t_elem **node, t_data *mini)
{
	char	*tmp;

	tmp = NULL;
	if ((*node)->type == DOUBLE_QUOTE || (*node)->type == QOUTE)
		tmp = parse_quo(tmp, node, (*node)->type, mini);
	else if ((*node)->type == ENV)
	{
		tmp = get_env(mini->enviro, (*node)->content + 1);
		if (*node)
			*node = (*node)->next;
	}
	else if ((*node)->type == WORD)
	{
		tmp = ft_strdup((*node)->content);
		if (*node)
			*node = (*node)->next;
	}
	return (tmp);
}

void	check_redir(t_node_cmd *new, enum e_token type)
{
	if (new->redir_in && (type == REDIR_IN || type == HERE_DOC))
	{
		free(new->in_name);
		new->in_name = NULL;
		free(new->redir_in);
		new->redir_in = NULL;
	}
	else if ((new->redir_out && type == REDIR_OUT)
		|| (new->redir_out && type == DREDIR_OUT))
	{
		free(new->out_name);
		new->out_name = NULL;
		free(new->redir_out);
		new->redir_out = NULL;
	}
}

void	parse_redir(t_elem **node, t_data *mini, t_node_cmd	*new)
{
	enum e_token	type;
	char			*tmp;

	type = (*node)->type;
	check_redir(new, type);
	if (type == REDIR_OUT || type == DREDIR_OUT)
		new->redir_out = get_redir_symb(type);
	else
		new->redir_in = get_redir_symb(type);
	while ((*node)->type != WORD && (*node)->type != ENV
		&& (*node)->type != DOUBLE_QUOTE && (*node)->type != QOUTE)
		*node = (*node)->next;
	tmp = get_name(node, mini);
	if (type == REDIR_OUT || type == DREDIR_OUT)
		new->out_name = tmp;
	else
		new->in_name = tmp;
}

t_node_cmd	*parsing(t_list_n *list, t_data *mini)
{
	t_node_cmd	*commands;
	t_node_cmd	*new;
	t_elem		*tmp;
	int			size;

	tmp = list->head;
	commands = NULL;
	while (tmp)
	{
		size = count_args(tmp);
		new = new_cmd_node(&tmp, size, mini);
		ft_add_cmd_end(&commands, new);
		if (tmp)
			tmp = tmp->next;
	}
	return (commands);
}
