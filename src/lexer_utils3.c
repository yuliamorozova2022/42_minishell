/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_elem	*skip_space(t_elem *ptr, int opt)
{
	while (ptr && ptr->type == WHITE_SPACE)
	{
		if (opt)
			ptr = ptr->next;
		else
			ptr = ptr->prev;
	}
	return (ptr);
}

int	is_redir(enum e_token type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == DREDIR_OUT || type == HERE_DOC);
}
