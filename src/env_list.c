/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:52 by ymorozov          #+#    #+#             */
/*   Updated: 2023/09/13 13:51:28 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*create_env_list(char **env)
{
	t_node	*head;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		ft_add_end(&head, env[i]);
		i++;
	}
	return (head);
}

void	remove_env_list(t_node **head)
{
	t_node	*tmp;
	t_node	*current;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		tmp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
}

void	ft_add_end(t_node **head, char *env)
{
	t_node	*new_node;
	t_node	*current;

	new_node = ft_calloc(sizeof(t_node), 1);
	if (new_node == NULL)
		return ;
	new_node->key = ft_separate_key(env);
	new_node->eq = '=';
	new_node->value = ft_separate_value(env);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

char	*ft_separate_key(char *env)
{
	int		i;
	char	*key;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), (i + 1));
	if (key == NULL)
		return (NULL);
	i = 0;
	while (env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ft_separate_value(char *env)
{
	int		i;
	int		y;
	char	*value;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	y = i;
	while (env[y])
		y++;
	value = ft_calloc(sizeof(char), ((y - i) + 1));
	if (!value)
		return (NULL);
	y = 0;
	while (env[i])
	{
		value[y] = env[i];
		i++;
		y++;
	}
	value[y] = '\0';
	return (value);
}
