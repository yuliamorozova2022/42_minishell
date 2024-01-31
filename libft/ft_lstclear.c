/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:29:03 by msulc             #+#    #+#             */
/*   Updated: 2023/02/08 13:29:06 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*body;
	t_list	*temp;

	if (!lst || !(*del))
		return ;
	body = *lst;
	while (body != NULL)
	{
		temp = body;
		del(body->content);
		body = body->next;
		free(temp);
	}
	*lst = NULL;
}
