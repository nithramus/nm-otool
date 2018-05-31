/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_symbol_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:08:39 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 11:39:17 by bandre           ###   ########.fr       */
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
		if ((char*)symtab + sizeof(struct nlist_64) > file_struct->file + file_struct->file_length)
		{
			file_struct->is_valid = 0;
			file_struct->error = "Invalid file";
			return ;
		}
		if (!(symbol = malloc(sizeof(t_symbol))))
		{
			file_struct->is_valid = 0;
			file_struct->error = "Malloc failed";
			return ;
		}
		if (stringable + reverse_32(&symtab->n_un.n_strx, file_struct) < (void*)file_struct->file + file_struct->file_length)
			symbol->name = stringable + reverse_32(&symtab->n_un.n_strx, file_struct);
		else
			symbol->name = "bad string index";
		symbol->type = symtab->n_type;
		symbol->section = (int)symtab->n_sect;
		add_back_maillon(symbols, symbol);
		symbol->value = reverse(&symtab->n_value, file_struct);
		if (file_struct->is_64)
			symtab = (void*)symtab + sizeof(struct nlist_64);
		else
			symtab = (void*)symtab + sizeof(struct nlist);
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
	lc = (struct load_command*)(file_struct->file + file_struct->size_of_header);
	while ((uint32_t)i < file_struct->nb_command)
	{
		if ((char*)lc + sizeof(struct load_command)> file_struct->file + file_struct->file_length)
		{
			file_struct->is_valid = 0;
			file_struct->error = "Invalid file";
			return ;
		}
		if (file_struct->file_length + (void*)file_struct->file <= (void*)lc)
		{
			file_struct->is_valid = 0;
			file_struct->error = "Invalid file";
			return ;
		}
		if (reverse_32(&lc->cmd, file_struct) == LC_SYMTAB)
			get_all_symbols(symbols, file_struct, (struct symtab_command*)lc);
		else if (file_struct->is_64 && reverse_32(&lc->cmd, file_struct) == LC_SEGMENT_64)
			get_sections_64(sections, (struct segment_command_64*)lc, &j, file_struct);
		else if (!file_struct->is_64 && reverse_32(&lc->cmd, file_struct)== LC_SEGMENT)
			get_sections_32(sections, (struct segment_command*)lc, &j, file_struct);
		lc = (void*)lc + reverse_32(&lc->cmdsize, file_struct);
		i++;
	}
}
