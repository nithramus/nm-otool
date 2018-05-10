/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:21:41 by bandre            #+#    #+#             */
/*   Updated: 2018/05/10 19:39:55 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	find_symbol(t_libft_chained_list **first, t_libft_chained_list *section, void *params)
{
	t_search_section	*search;
	t_section			*sect;

	sect = (t_section*)section->data;
	search = (t_search_section*)params;
	if (sect->num == search->value)
	{

	}
}

void	show_symbols(
	t_libft_chained_list **symbols,
	t_libft_chained_list *sections,
	t_mainstruct *fiel_struct)
{

}