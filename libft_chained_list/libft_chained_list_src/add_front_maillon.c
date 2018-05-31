/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front_maillon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:05:37 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 19:05:57 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

void	add_front_maillon(t_libft_chained_list **first, void *data)
{
	t_libft_chained_list *maillon;

	if (!(*first))
	{
		*first = create_maillon(NULL, NULL, data);
	}
	else
	{
		maillon = create_maillon(*first, NULL, data);
		(*first)->before = maillon;
		*first = maillon;
	}
}
