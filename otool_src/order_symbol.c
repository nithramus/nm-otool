/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:48:00 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 13:51:47 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	file_done(
	t_libft_chained_list *maillon,
	void *param)
{
	t_search		*search;
	t_mainstruct	*file_struct;

	search = (t_search*)param;
	file_struct = (t_mainstruct *)maillon->data;
	if (file_struct->file == search->searched)
		search->found = 1;
}

void	order(
	t_libft_chained_list *maillon,
	void *params)
{
	t_symbol	*sym1;
	t_symbol	*sym2;
	void		*tmp;
	int			*yolo;

	yolo = (int*)params;
	if (!maillon->next)
		return ;
	sym1 = (t_symbol*)maillon->data;
	sym2 = (t_symbol*)maillon->next->data;
	if (ft_strcmp(sym1->name, sym2->name) > 0 ||
		(ft_strcmp(sym1->name, sym2->name) == 0 && sym2->value < sym1->value))
	{
		*yolo = 1;
		tmp = maillon->data;
		maillon->data = maillon->next->data;
		maillon->next->data = tmp;
	}
}

void	order_symbol(t_libft_chained_list **symbols)
{
	int		ended;

	ended = 1;
	while (ended == 1)
	{
		ended = 0;
		function_on_chained_list(symbols, order, &ended);
	}
}
