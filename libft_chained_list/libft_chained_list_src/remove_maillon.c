/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_maillon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:21:46 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 19:35:14 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

void	free_maillon(t_libft_chained_list *maillon, void (*delete_data)(void*))
{
	(*delete_data)(maillon->data);
	free(maillon);
}

void	remove_maillon(
	t_libft_chained_list **first,
	t_libft_chained_list *maillon,
	void (*delete_data)(void*))
{
	if (!maillon)
	{
		ft_puterror("Sending NULL as maillon");
		return ;
	}
	if (!maillon->before)
	{
		if (!maillon->next)
		{
			free_maillon(maillon, delete_data);
			*first = NULL;
		}
		else
		{
			*first = (*first)->next;
			(*first)->before = NULL;
			free_maillon(maillon, delete_data);
		}
		return ;
	}
	maillon->before->next = maillon->next;
	if (maillon->next)
		maillon->next->before = maillon->before;
	free_maillon(maillon, delete_data);
}
