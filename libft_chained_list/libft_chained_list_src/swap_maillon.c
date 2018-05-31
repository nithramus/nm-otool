/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_maillon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:22:56 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 17:35:30 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

void	swap(t_libft_chained_list *dest, t_libft_chained_list *src)
{
	void *tmp;

	tmp = dest->data;
	dest->data = src->data;
	src->data = tmp;
}

void	swap_maillon(t_libft_chained_list **first,
	int (*function)(void*, void*))
{
	t_libft_chained_list	*tmp;
	int						retour;

	retour = 0;
	tmp = *first;
	while (tmp && tmp->next)
	{
		retour = (*function)(tmp->data, tmp->data);
		if (retour)
		{
			swap(tmp, tmp->next);
		}
		tmp = tmp->next;
	}
}
