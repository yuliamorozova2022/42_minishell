/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_cmd_end(t_node_cmd **head, t_node_cmd *new)
{
	t_node_cmd	*current;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != 0)
		current = current->next;
	current->next = new;
}

t_node_cmd	*new_cmd_node_init(int size, int *i)
{
	t_node_cmd	*new;

	*i = 0;
	new = ft_calloc(sizeof(t_node_cmd), 1);
	if (new == NULL)
		return (NULL);
	new->path = NULL;
	new->cmd = ft_calloc((size + 1), sizeof(char *));
	if (new->cmd == NULL)
		return (NULL);
	new->redir_in = NULL;
	new->in_name = NULL;
	new->in_fd = -2;
	new->redir_out = NULL;
	new->out_name = NULL;
	new->out_fd = -3;
	new->next = 0;
	return (new);
}

t_node_cmd	*new_cmd_node(t_elem **list, int size, t_data *mini)
{
	t_node_cmd	*new;
	int			i;

	new = new_cmd_node_init(size, &i);
	if (new == NULL)
		return (NULL);
	while ((*list) && (*list)->type != PIPE_LINE)
	{
		if ((*list)->type == WORD)
			parse_word(list, new->cmd, &i);
		else if ((*list)->type == ENV)
			parse_env(list, new->cmd, &i, mini);
		else if ((*list)->type == WHITE_SPACE)
			(*list) = (*list)->next;
		else if ((*list)->type == DOUBLE_QUOTE || (*list)->type == QOUTE)
		{
			new->cmd[i] = parse_quo(new->cmd[i], list, (*list)->type, mini);
			if (new->cmd[i])
				i++;
		}
		else if (is_redir((*list)->type))
			parse_redir(list, mini, new);
	}
	new->cmd[i] = NULL;
	return (new);
}

static void	remove_cmd_list_ext(t_node_cmd *current)
{
	int	i;

	i = 0;
	if (current->path)
		free(current->path);
	if (current->redir_in)
		free(current->redir_in);
	if (current->in_name)
		free(current->in_name);
	if (current->redir_out)
		free(current->redir_out);
	if (current->out_name)
		free(current->out_name);
	if (current->cmd)
	{
		while (current->cmd[i])
			free(current->cmd[i++]);
		free(current->cmd);
	}
	if (current->in_fd > 0)
		close(current->in_fd);
	if (current->out_fd > 0)
		close(current->out_fd);
}

void	remove_cmd_list(t_node_cmd **head)
{
	t_node_cmd	*tmp;
	t_node_cmd	*current;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		tmp = current->next;
		remove_cmd_list_ext(current);
		free(current);
		current = tmp;
	}
	*head = NULL;
}
