/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:17:58 by ryatan            #+#    #+#             */
/*   Updated: 2026/06/01 13:59:36 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **arr)
{
	size_t	i;

	i = 0;
	while (i < arr_len(arr))
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

//t_status	free_token_list(t_token *token_list)
//{
//	if (!token_list)
//		return (E_FAIL);
//
//}
