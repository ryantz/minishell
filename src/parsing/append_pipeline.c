/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:12:56 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/08 16:53:02 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_pipeline(t_pipeline **head, t_pipeline *new)
{
	t_pipeline	*ptr;

	if (!*head)
	{
		*head = new;
		return ;
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
