/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:29:35 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/25 20:36:03 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void	del(void *content)
//{
//	if (content)
//	{
//		printf("freeing content\n");
//		free(content);
//	}
//}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

//int main(void)
//{
//    t_list *node;
//
//    // Allocate node
//    node = malloc(sizeof(t_list));
//    if (!node)
//        return (1);
//
//    // Allocate and assign content
//    node->content = malloc(6);
//    if (!node->content)
//    {
//        free(node);
//        return (1);
//    }
//
//    // Manually write content (no snprintf)
//    char *str = (char *)node->content;
//    str[0] = 'H';
//    str[1] = 'e';
//    str[2] = 'l';
//    str[3] = 'l';
//    str[4] = 'o';
//    str[5] = '\0';
//
//    node->next = NULL;
//
//    printf("Before deletion:\n");
//    printf("node->content = %s\n", (char *)node->content);
//
//    // Test ft_lstdelone
//    ft_lstdelone(node, del);
//
//    printf("After deletion: %s\n", (char *)node->content);
//    printf("Node should be freed and del() should have been called.\n");
//
//    return (0);
//}
