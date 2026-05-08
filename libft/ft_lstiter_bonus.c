/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:03:59 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/25 20:54:25 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void print_content(void *content)
//{
//    printf("Content: %s\n", (char *)content);
//}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

//int main(void)
//{
//    t_list *n1;
//    t_list *n2;
//    t_list *n3;
//
//    // Allocate nodes
//    n1 = malloc(sizeof(t_list));
//    n2 = malloc(sizeof(t_list));
//    n3 = malloc(sizeof(t_list));
//
//    if (!n1 || !n2 || !n3)
//        return (1);
//
//    // Allocate content
//    n1->content = malloc(6);
//    n2->content = malloc(6);
//    n3->content = malloc(6);
//
//    if (!n1->content || !n2->content || !n3->content)
//        return (1);
//
//    // Fill content manually (only printf allowed)
//    char *s1 = n1->content;
//    s1[0] = 'H'; s1[1] = 'e'; s1[2] = 'l'; s1[3] = 'l'; s1[4] = 'o';
//    s1[5] = '\0';
//
//    char *s2 = n2->content;
//    s2[0] = '4'; s2[1] = '2'; s2[2] = 'S'; s2[3] = 'c'; s2[4] = 'h';
//    s2[5] = '\0';
//
//    char *s3 = n3->content;
//    s3[0] = 'B'; s3[1] = 'y'; s3[2] = 'e'; s3[3] = '\0';
//
//    // Link nodes
//    n1->next = n2;
//    n2->next = n3;
//    n3->next = NULL;
//
//    printf("Testing ft_lstiter:\n");
//    ft_lstiter(n1, print_content);
//
//    // Free memory manually (since this test doesn't call ft_lstclear)
//    free(n1->content);
//    free(n2->content);
//    free(n3->content);
//    free(n1);
//    free(n2);
//    free(n3);
//
//    return (0);
//}
