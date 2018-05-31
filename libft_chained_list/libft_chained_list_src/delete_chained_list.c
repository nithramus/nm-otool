/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_chained_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:07:04 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 19:07:54 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

void	free_chained_list(
	t_libft_chained_list *maillon, void *params)
{
	free(maillon);
	params += 1 - 1;
}

void	delete_chained_list(t_libft_chained_list **first,
	void delete_data(void*))
{
	simple_function_on_chained_list(first, delete_data);
	function_on_chained_list(first, free_chained_list, NULL);
	*first = NULL;
}
