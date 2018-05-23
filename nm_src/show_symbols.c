/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:21:41 by bandre            #+#    #+#             */
/*   Updated: 2018/05/23 20:23:20 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	find_symbol(
	t_libft_chained_list **first,
	t_libft_chained_list *maillon,
	void *params)
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
	if (!search.type)
	{
		if ((symbol->type & N_INDR) == N_INDR)
			letter = 'I';
		else if ((symbol->type & N_ABS) == N_ABS)		
			letter = 'A';
		else
			letter = 'U';
	}
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

void	print_symbol_32(
	t_libft_chained_list **first,
	t_libft_chained_list *sym,
	void *params)
{
	t_symbol			*symbol;

	symbol = (t_symbol*)sym->data;
	if (symbol->type & N_STAB)
		return ;	
	if (!symbol->value && symbol->section == 0)
		ft_printf("         ");
	else
		ft_printf("%08lx ", symbol->value);
	print_letter(symbol, params);
	ft_putendl(symbol->name);
}

void	print_symbol_64(
	t_libft_chained_list **first,
	t_libft_chained_list *sym,
	void *params)
{
	t_symbol			*symbol;

	symbol = (t_symbol*)sym->data;
	if (symbol->type & N_STAB)
		return ;
	if (!symbol->value && symbol->section == 0)
		ft_printf("                 ");
	else
		ft_printf("%016lx ", symbol->value);
	print_letter(symbol, params);
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
}
