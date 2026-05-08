/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:38:31 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/25 19:17:27 by ryatan           ###   ########.fr       */
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

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	else
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}

//int main(void)
//{
//    t_list  *n1;
//    t_list  *n2;
//    t_list  *n3;
//    t_list  *list;
//
//    // Allocate 3 nodes
//    n1 = malloc(sizeof(t_list));
//    n2 = malloc(sizeof(t_list));
//    n3 = malloc(sizeof(t_list));
//
//    if (!n1 || !n2 || !n3)
//        return (1);
//
//    // Allocate content for each node
//    n1->content = malloc(6);
//    n2->content = malloc(6);
//    n3->content = malloc(6);
//
//    if (!n1->content || !n2->content || !n3->content)
//        return (1);
//
//    // Fill content manually (no snprintf)
//    char *s1 = n1->content;
//    s1[0] = 'H'; s1[1] = 'e'; s1[2] = 'l'; s1[3] = 'l'; s1[4] = 'o';
//    s1[5] = '\0';
//
//    char *s2 = n2->content;
//    s2[0] = 'W'; s2[1] = 'o'; s2[2] = 'r'; s2[3] = 'l'; s2[4] = 'd';
//    s2[5] = '\0';
//
//    char *s3 = n3->content;
//    s3[0] = '4'; s3[1] = '2'; s3[2] = '!'; s3[3] = '\0';
//
//    // Chain the list: n1 -> n2 -> n3
//    n1->next = n2;
//    n2->next = n3;
//    n3->next = NULL;
//
//    list = n1;
//
//    printf("Before ft_lstclear:\n");
//    printf("Node1: %s\n", (char *)list->content);
//    printf("Node2: %s\n", (char *)list->next->content);
//    printf("Node3: %s\n", (char *)list->next->next->content);
//
//    // Test ft_lstclear
//    ft_lstclear(&list, del);
//
//    printf("\nAfter ft_lstclear:\n");
//    if (list == NULL)
//        printf("List pointer is now NULL. \n");
//    else
//        printf("List pointer is NOT NULL. \n");
//
//    return (0);
//}
