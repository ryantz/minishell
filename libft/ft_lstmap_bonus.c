/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:48:10 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/25 20:55:39 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void *add_star(void *content)
//{
//    char *str = (char *)content;
//    int len = 0;
//
//    if (!str)
//        return (NULL);   
//
//    while (str[len])
//        len++;
//
//    char *new = malloc(len + 2);
//    if (!new)
//        return (NULL);  
//
//    for (int i = 0; i < len; i++)
//        new[i] = str[i];
//
//    new[len] = '*';
//    new[len + 1] = '\0';
//
//    return (new);      
//}

//void del_content(void *content)
//{
//    printf("del() called -> freeing content\n");
//    free(content);
//}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
			return (ft_lstclear(&new_list, del), NULL);
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

//int main(void)
//{
//    t_list *n1;
//    t_list *n2;
//    t_list *n3;
//    t_list *mapped;
//
//    // Allocate nodes
//    n1 = malloc(sizeof(t_list));
//    n2 = malloc(sizeof(t_list));
//    n3 = malloc(sizeof(t_list));
//
//    // Allocate content
//    n1->content = malloc(6);
//    n2->content = malloc(4);
//    n3->content = malloc(4);
//
//    // Fill content manually
//    char *s1 = n1->content; s1[0]='H'; s1[1]='e'; s1[2]='l'; s1[3]='l'; 
//    s1[4]='o'; s1[5]='\0';
//    char *s2 = n2->content; s2[0]='4'; s2[1]='2'; s2[2]='\0';
//    char *s3 = n3->content; s3[0]='B'; s3[1]='y'; s3[2]='e'; s3[3]='\0';
//
//    // Link nodes
//    n1->next = n2;
//    n2->next = n3;
//    n3->next = NULL;
//
//    printf("Original list:\n");
//    printf("%s\n", (char *)n1->content);
//    printf("%s\n", (char *)n2->content);
//    printf("%s\n", (char *)n3->content);
//
//    // ---- Test ft_lstmap ----
//    mapped = ft_lstmap(n1, add_star, del_content);
//
//    printf("\nMapped list:\n");
//    t_list *tmp = mapped;
//    while (tmp)
//    {
//        printf("%s\n", (char *)tmp->content);
//        tmp = tmp->next;
//    }
//
//    // ---- Free original list ----
//    free(n1->content); free(n1);
//    free(n2->content); free(n2);
//    free(n3->content); free(n3);
//
//    // ---- Free mapped list ----
//    tmp = mapped;
//    while (tmp)
//    {
//        t_list *next = tmp->next;
//        del_content(tmp->content);
//        free(tmp);
//        tmp = next;
//    }
//
//    return 0;
//}
