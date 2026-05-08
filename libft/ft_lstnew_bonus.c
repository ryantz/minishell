/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:31:09 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/22 14:37:13 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

//int	main(void)
//{
//	t_list *head;
//	char *hello;
//
//	hello = "hellol";
//	head = ft_lstnew(hello);
//	printf("%s\n", (char *)head->content);
//	return (0);
//}
