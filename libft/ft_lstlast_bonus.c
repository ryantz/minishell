/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:37:55 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/22 15:53:11 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

//int	main(void)
//{
//	t_list	*lst;
//	t_list	*another;
//	t_list	*first;
//	t_list	*test;
//
//	lst = ft_lstnew("stranger");
//	another = ft_lstnew("there");
//	first = ft_lstnew("hello");
//	ft_lstadd_front(&lst, another);
//	ft_lstadd_front(&lst, first);
//	test = ft_lstlast(lst);
//	printf("%s\n", (char*)test->content);
//	printf("list size:%d\n", ft_lstsize(lst));
//}
