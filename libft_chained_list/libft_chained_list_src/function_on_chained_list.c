/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_on_chained_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:10:31 by bandre            #+#    #+#             */
/*   Updated: 2018/05/24 15:03:34 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

void	simple_function_on_chained_list(
	t_libft_chained_list **first,
	void (*function)(void*))
{
	t_libft_chained_list *tmp;
	t_libft_chained_list *tmp2;

	tmp = *first;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = tmp->next;
		(*function)(tmp->data);
		tmp = tmp->next;
		tmp = tmp2;
	}
}

void	function_on_chained_list(
	t_libft_chained_list **first,
	void (*function)(t_libft_chained_list*, void*),
	void *params)
{
	t_libft_chained_list *tmp;
	t_libft_chained_list *tmp2;

	tmp = *first;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = tmp->next;
		(*function)(tmp, params);
		tmp = tmp2;
	}
}
