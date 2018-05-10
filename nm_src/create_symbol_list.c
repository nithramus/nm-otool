/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_symbol_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:08:39 by bandre            #+#    #+#             */
/*   Updated: 2018/05/10 18:05:33 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// t_symbol	*create_t_symbol_32(t_libft_chained_list **symbols, void *ptr)
// {
// 	//malloc
// }

void	get_all_symbols(
	t_libft_chained_list **symbols,
	t_mainstruct *file_struct,
	struct symtab_command *st)
{
	void			*stringable;
	struct nlist_64	*symtab;
	int				i;
	t_symbol		*symbol;


	i = 0;
	stringable = (void*)file_struct->file + reverse(&st->stroff,4 ,file_struct);
	symtab = (void*)file_struct->file + reverse(&st->symoff, 4, file_struct);
	while (i < reverse(&st->nsyms, 4, file_struct))
	{
		symbol = malloc(sizeof(t_symbol));
		if (!symbol)
		{
			ft_putendl("malloc failed");
			quit_clean();
		}
		// VERIFIER SYMTABSIZE, et stringable jump
		ft_putendl(stringable + symtab->n_un.n_strx);
		symbol->name = stringable + symtab->n_un.n_strx;
		symbol->value = symtab->n_value;
		symbol->type = symtab->n_type;
		symbol->section = symtab->n_sect;
		add_back_maillon(symbols, symbol);

		if (file_struct->is_64)
			symtab = (void*)symtab + sizeof(struct nlist_64);
		else
			symtab = (void*)symtab + sizeof(struct nlist);
		i++;
	}

}

void	create_symbol_list(t_libft_chained_list **symbols, t_libft_chained_list **sections, t_mainstruct *file_struct)
{
	struct load_command *lc;
	int			i;

	i = 0;
	lc = (void*)(struct load_command*)(file_struct->file + file_struct->size_of_header);
	while ((uint32_t)i < file_struct->nb_command)
	{
		// check_size_loadcmsg();
	// TODO: reverse
		if (lc->cmd == LC_SYMTAB)
		{
			ft_putendl("found the thing");
			get_all_symbols(symbols, file_struct, (struct symtab_command*)lc);
		}
		else if (file_struct->is_64 && lc->cmd == LC_SEGMENT_64)
		{
			ft_putendl("SEGMENT 64");
			get_sections_64(sections, (struct segment_command_64*)lc);
		}
		else if (!file_struct->is_64 && lc->cmd == LC_SEGMENT)
		{
			// get_sections_32(sections,  (struct segment_command_64*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}