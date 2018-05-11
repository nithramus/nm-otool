/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:21:41 by bandre            #+#    #+#             */
/*   Updated: 2018/05/11 14:20:56 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


void	find_symbol(t_libft_chained_list **first, t_libft_chained_list *maillon, void *params)
{
	t_search_section	*search;
	t_section			*sect;

	sect = (t_section*)maillon->data;
	search = (t_search_section*)params;
	if (sect->num == search->value)
	{
		search->type = sect->sect_name;
	}
}

void	print_letter(t_symbol *symbol, t_libft_chained_list **section)
{
	t_search_section	search;
	char				letter;
	
	search.type = NULL;
	search.value = (int)symbol->section;
	function_on_chained_list(section, find_symbol, &search);
	// ft_printf("%s ", search.type);
	if (!search.type)
		letter = 'U';
	else if (ft_strcmp(search.type, "__text") == 0)
		letter = 'T';
	else if (ft_strcmp(search.type, "__bss") == 0)
		letter = 'B';
	// else if (ft_strcmp(search.type, "__common") == 0)
	// 	letter = 'C';
	else if (ft_strcmp(search.type, "__data") == 0)
		letter = 'D';
	else
		letter = 'S';
	if (!(symbol->type & N_EXT))
		letter += 32;
	ft_printf("%c ", letter);
}

void	print_symbol(t_libft_chained_list **first, t_libft_chained_list *sym, void *params)
{
	t_symbol			*symbol;

	symbol = (t_symbol*)sym->data;
	if (symbol->type & N_STAB)
		return ;
	if (symbol->value)
		ft_printf("%016lx ", symbol->value);
	else
		ft_printf("                 ");
	print_letter(symbol, params);
	ft_putendl(symbol->name);
	
}

void	show_symbols(
	t_libft_chained_list **symbols,
	t_libft_chained_list **sections,
	t_mainstruct *file_struct)
{
	function_on_chained_list(symbols, print_symbol, sections);

}