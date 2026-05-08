/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:17:30 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:30:48 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (lst == NULL)
		return (0);
	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

//int	main(void)
//{
//	t_list	*lst;
//	t_list	*another;
//
//	lst = ft_lstnew("there");
//	another = ft_lstnew("hello");
//	ft_lstadd_front(&lst, another);
//	printf("%s\n", (char*)lst->content);
//	printf("list size:%d\n", ft_lstsize(lst));
//}
