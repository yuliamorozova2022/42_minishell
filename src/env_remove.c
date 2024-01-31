/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_remove_node_ext(t_node *to_remove)
{
	free(to_remove->key);
	free(to_remove->value);
	free(to_remove);
}

void	ft_remove_node(t_node **head, char *key)
{
	t_node	*current;
	t_node	*prev;
	t_node	*to_remove;
	int		first;

	if (*head == NULL || !key)
		return ;
	current = *head;
	first = TRUE;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			to_remove = current;
			if (first)
				*head = current->next;
			else
				prev->next = current->next;
			ft_remove_node_ext(to_remove);
			return ;
		}
		first = FALSE;
		prev = current;
		current = current->next;
	}
}
