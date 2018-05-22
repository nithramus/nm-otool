/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_symbol_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:08:39 by bandre            #+#    #+#             */
/*   Updated: 2018/05/18 17:27:06 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	get_all_symbols(
	t_libft_chained_list **symbols,
	t_mainstruct *file_struct,
	struct symtab_command *st)
{
	void			*stringable;
	struct nlist_64	*symtab;
	uint32_t		i;
	t_symbol		*symbol;

	i = 0;
	stringable = (void*)file_struct->file + reverse_32(&st->stroff, file_struct);
	symtab = (void*)file_struct->file + reverse_32(&st->symoff, file_struct);
	while (i < reverse_32(&st->nsyms, file_struct))
	{
		if (!(symbol = malloc(sizeof(t_symbol))))
			quit_clean("malloc failed");
		// VERIFIER SYMTABSIZE, et stringable jump
		if (stringable + symtab->n_un.n_strx < (void*)file_struct->file + file_struct->file_length)
			symbol->name = stringable + symtab->n_un.n_strx;
		else
			symbol->name = "bad string index";
		symbol->type = symtab->n_type;
		symbol->section = (int)symtab->n_sect;
		add_back_maillon(symbols, symbol);
		if (file_struct->is_64)
		{
			symbol->value = symtab->n_value;
			symtab = (void*)symtab + sizeof(struct nlist_64);
		}
		else
		{
			symbol->value = (uint64_t)(*(uint32_t*)&symtab->n_value);
			symtab = (void*)symtab + sizeof(struct nlist);
		}
		i++;
	}
}

void	create_symbol_list(
		t_libft_chained_list **symbols,
		t_libft_chained_list **sections,
		t_mainstruct *file_struct)
{
	struct load_command	*lc;
	int					i;
	int					j;

	i = 0;
	j = 1;
	lc = (struct load_command*)(file_struct->file
		+ file_struct->size_of_header);
	while ((uint32_t)i < file_struct->nb_command)
	{
	// check_size_loadcmsg();
	// TODO: reverse
		if (file_struct->file_length + (void*)file_struct->file <= (void*)lc)
		{
			file_struct->is_valid = 0;
			file_struct->error = "File to short1";
			return ;
		}
		if (lc->cmd == LC_SYMTAB)
			get_all_symbols(symbols, file_struct, (struct symtab_command*)lc);
		else if (file_struct->is_64 && lc->cmd == LC_SEGMENT_64)
			get_sections_64(sections, (struct segment_command_64*)lc, &j);
		else if (!file_struct->is_64 && lc->cmd == LC_SEGMENT)
			get_sections_32(sections, (struct segment_command*)lc, &j);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}
