/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_word(t_list_n *tokens, char *str, enum e_state state)
{
	int	i;

	i = 0;
	while (!in_charset(str[i]))
		i++;
	add_tail(tokens, new_elem(str, i, WORD, state));
	return (i);
}

int	get_env_token(t_list_n *tokens, char *str, enum e_state state)
{
	int	i;

	i = 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		while (is_alphanum(str[i]) && str[i] != '\n' && str[i] != '\0')
			i++;
	add_tail(tokens, new_elem(str, i, ENV, state));
	return (i);
}

int	make_token_redir(t_list_n *tokens, char *str, int idx, enum e_state state)
{
	int	i;

	i = idx;
	if (str[idx] == '<')
	{
		if (str[idx + 1] && str[idx + 1] == '<')
			add_tail(tokens, new_elem(str + idx++, 2, HERE_DOC, state));
		else
			add_tail(tokens, new_elem(str + idx, 1, REDIR_IN, state));
		idx++;
	}
	else if (str[idx] == '>')
	{
		if (str[idx + 1] && str[idx + 1] == '>')
			add_tail(tokens, new_elem(str + idx++, 2, DREDIR_OUT, state));
		else
			add_tail(tokens, new_elem(str + idx, 1, REDIR_OUT, state));
		idx++;
	}
	return (idx - i);
}

int	ft_make_token(t_list_n *tokens, char *str, int i, enum e_state *state)
{
	if (in_charset(str[i]) != 1)
		i += get_word(tokens, str + i, *state);
	else if (str[i] == '\'')
		quotes_state(tokens, str + i++, state, 1);
	else if (str[i] == '"')
		quotes_state(tokens, str + i++, state, 2);
	else if (str[i] == '$')
	{
		if (str[i + 1] && in_charset(str[i + 1]))
			add_tail(tokens, new_elem(str + i++, 1, WORD, *state));
		else
			i += get_env_token(tokens, str + i, *state);
	}
	else if (str[i] == '>' || str[i] == '<')
		i += make_token_redir(tokens, str, i, *state);
	else if (str[i] == '|')
		add_tail(tokens, new_elem(str + i++, 1, PIPE_LINE, *state));
	else if (ft_isspace(str[i]))
		add_tail(tokens, new_elem(str + i++, 1, WHITE_SPACE, *state));
	return (i);
}

t_list_n	*lexer(char *line)
{
	t_list_n		*tokens;
	int				i;
	enum e_state	state;

	i = 0;
	state = GENERAL;
	tokens = NULL;
	tokens = init_list(tokens);
	if (tokens)
	{
		while (line[i])
			i = ft_make_token(tokens, line, i, &state);
	}
	return (tokens);
}
