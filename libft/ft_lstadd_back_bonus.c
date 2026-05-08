/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:56:55 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 22:23:04 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
}

//int	main(void)
//{
//	t_list	*lst;
//	t_list	*another;
//	t_list	*first;
//	t_list	*last;
//	t_list	*test;
//
//	lst = ft_lstnew("stranger");
//	another = ft_lstnew("there");
//	first = ft_lstnew("hello");
//	last = ft_lstnew("!!!");
//
//	ft_lstadd_front(&lst, another);
//	ft_lstadd_front(&lst, first);
//	ft_lstadd_back(&lst, last);
//	
//	test = ft_lstlast(lst);
//
//	printf("%s\n", (char*)test->content);
//	printf("list size:%d\n", ft_lstsize(lst));
//	return (0);
//}
