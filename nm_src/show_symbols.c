/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:21:41 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 17:38:01 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_letter_32(t_symbol *symbol, t_search_section search)
{
	char				letter;

	if (!search.type && (symbol->type & N_INDR) == N_INDR)
		letter = 'I';
	else if (!search.type && (symbol->type & N_ABS) == N_ABS)
		letter = 'A';
	else if (!search.type)
		letter = 'U';
	else if (ft_strcmp(search.type, "__text") == 0)
		letter = 'T';
	else if (ft_strcmp(search.type, "__bss") == 0)
		letter = 'B';
	else if (ft_strcmp(search.type, "__data") == 0)
		letter = 'D';
	else
		letter = 'S';
	if (!symbol->value && symbol->section == 0)
		ft_printf("         ");
	else
		ft_printf("%08lx ", symbol->value);
	if (!(symbol->type & N_EXT))
		letter += 32;
	ft_printf("%c ", letter);
}

void	print_letter_64(t_symbol *symbol, t_search_section search)
{
	char				letter;

	if (!search.type && (symbol->type & N_INDR) == N_INDR)
		letter = 'I';
	else if (!search.type && (symbol->type & N_ABS) == N_ABS)
		letter = 'A';
	else if (!search.type)
		letter = 'U';
	else if (ft_strcmp(search.type, "__text") == 0)
		letter = 'T';
	else if (ft_strcmp(search.type, "__bss") == 0)
		letter = 'B';
	else if (ft_strcmp(search.type, "__data") == 0)
		letter = 'D';
	else
		letter = 'S';
	if (!symbol->value && letter == 'U')
		ft_printf("                 ");
	else
		ft_printf("%016llx ", symbol->value);
	if (!(symbol->type & N_EXT))
		letter += 32;
	ft_printf("%c ", letter);
}

void	print_symbol_32(
	t_libft_chained_list *sym,
	void *params)
{
	t_symbol			*symbol;
	t_search_section	search;

	symbol = (t_symbol*)sym->data;
	search.type = NULL;
	search.value = (int)symbol->section;
	function_on_chained_list(params, find_symbol, &search);
	if (symbol->type & N_STAB)
		return ;
	print_letter_32(symbol, search);
	ft_putendl(symbol->name);
}

void	print_symbol_64(
	t_libft_chained_list *sym,
	void *params)
{
	t_symbol			*symbol;
	t_search_section	search;

	symbol = (t_symbol*)sym->data;
	search.type = NULL;
	search.value = (int)symbol->section;
	function_on_chained_list(params, find_symbol, &search);
	if (symbol->type & N_STAB)
		return ;
	print_letter_64(symbol, search);
	ft_putendl(symbol->name);
}

void	show_symbols(
	t_libft_chained_list **symbols,
	t_libft_chained_list **sections,
	t_mainstruct *file_struct)
{
	if (file_struct->is_64)
		function_on_chained_list(symbols, print_symbol_64, sections);
	else
		function_on_chained_list(symbols, print_symbol_32, sections);
	delete_chained_list(symbols, free);
	delete_chained_list(sections, free);
}
