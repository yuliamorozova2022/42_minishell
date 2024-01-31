/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(char *s1, int n)
{
	char	*copy;
	size_t	s1_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	copy = malloc(sizeof(char) * (s1_len + 1));
	if (!copy)
		return (NULL);
	while (s1[i] && i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	is_alphanum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (TRUE);
	return (FALSE);
}

int	in_charset(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || ft_isspace(c) || c == 0);
}

void	quotes_state(t_list_n *tokens, char *str, enum e_state *state, int flag)
{
	enum e_state	e_state;
	enum e_token	e_type;

	if (flag == 1)
	{
		e_state = IN_QUOTE;
		e_type = QOUTE;
	}
	else
	{
		e_state = IN_DQUOTE;
		e_type = DOUBLE_QUOTE;
	}
	if (*state == GENERAL)
	{
		add_tail(tokens, new_elem(str, 1, e_type, *state));
		*state = e_state;
	}
	else if (*state == e_state)
	{
		*state = GENERAL;
		add_tail(tokens, new_elem(str, 1, e_type, *state));
	}
	else
		add_tail(tokens, new_elem(str, 1, e_type, *state));
}
