/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_err(t_elem *el)
{
	t_elem	*prev;
	t_elem	*next;

	prev = skip_space(el->prev, 0);
	next = skip_space(el->next, 1);
	if (!prev || !next)
		return (1);
	return (0);
}

int	redir_err(t_elem *ptr)
{
	t_elem	*next;

	next = skip_space(ptr->next, 1);
	if (!next || (next->type != WORD && next->type != ENV
			&& next->type != DOUBLE_QUOTE && next->type != QOUTE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_elem	*quotes_err(t_elem **ptr, enum e_token type)
{
	while (*ptr)
	{
		*ptr = (*ptr)->next;
		if (!*ptr || (*ptr)->type == type)
			break ;
	}
	if (!*ptr)
		write(2, "unclosed quotes detected.\n",
			ft_strlen("unclosed quotes detected.\n"));
	return (*ptr);
}

char	*get_redir_symb(enum e_token type)
{
	if (type == REDIR_IN)
		return (ft_strdup("<"));
	else if (type == REDIR_OUT)
		return (ft_strdup(">"));
	if (type == HERE_DOC)
		return (ft_strdup("<<"));
	if (type == DREDIR_OUT)
		return (ft_strdup(">>"));
	return (NULL);
}

int	sintax_check(t_list_n *list)
{
	t_elem	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
		{
			if (pipe_err(tmp))
				return (ft_perror("Syntax error: unexpected token near ", "|"));
		}
		if (is_redir(tmp->type))
		{
			if (redir_err(tmp))
				return (ft_perror("Syntax error in redirection ",
						get_redir_symb(tmp->type)));
		}
		else if (tmp->type == DOUBLE_QUOTE || tmp->type == QOUTE)
		{
			if (!quotes_err(&tmp, tmp->type))
				return (ft_perror("Syntax error in quotes", NULL));
		}
		tmp = tmp->next;
	}
	return (0);
}
