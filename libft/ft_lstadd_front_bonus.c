/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:34:55 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 22:14:26 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

//int	main(void)
//{
//	t_list	*new;
//	t_list	*head;
//	t_list	*empty;
//	char	*in;
//	char	*existing;
//
//	in = "hello";
//	existing = "there";
//	head = ft_lstnew(existing);
//	new = ft_lstnew(in);
//	ft_lstadd_front(&head, new);
//	ft_lstadd_front(&empty, new);
//	printf("non-empty list:%s\n", (char *)head->content);
//	printf("empty list:%s\n", (char *)empty->content);
//	return (0);
//}
