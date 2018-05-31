/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_symbol_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:08:39 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 17:00:05 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	invalid_file(t_mainstruct *f)
{
	f->is_valid = 0;
	f->error = "Invalid file";
}

void	get_all_symbols(
	t_libft_chained_list **symbols,
	t_mainstruct *f,
	struct symtab_command *st)
{
	void			*str;
	struct nlist_64	*s;
	uint32_t		i;
	t_symbol		*symbol;

	i = -1;
	str = (void*)f->file + r32(&st->stroff, f);
	s = (void*)f->file + r32(&st->symoff, f);
	while (++i < r32(&st->nsyms, f))
	{
		if ((char*)s + sizeof(struct nlist_64) > f->file + f->file_length ||
			!(symbol = malloc(sizeof(t_symbol))))
			return (invalid_file(f));
		if (str + r32(&s->n_un.n_strx, f) < (void*)f->file + f->file_length)
			symbol->name = str + r32(&s->n_un.n_strx, f);
		else
			symbol->name = "bad string index";
		symbol->type = s->n_type;
		symbol->section = (int)s->n_sect;
		add_back_maillon(symbols, symbol);
		symbol->value = reverse(&s->n_value, f);
		s = (void*)s + sizeof(struct nlist);
		if (f->is_64)
			s = (void*)s - sizeof(struct nlist) + sizeof(struct nlist_64);
	}
}

void	create_symbol_list(
		t_libft_chained_list **symbols,
		t_libft_chained_list **sections,
		t_mainstruct *f)
{
	struct load_command	*lc;
	int					i;
	int					j;

	i = 0;
	j = 1;
	lc = (struct load_command*)(f->file + f->size_of_header);
	while ((uint32_t)i < f->nb_command)
	{
		if ((char*)lc + sizeof(struct load_command) > f->file + f->file_length)
			return (invalid_file(f));
		if (f->file_length + (void*)f->file <= (void*)lc)
			return (invalid_file(f));
		if (r32(&lc->cmd, f) == LC_SYMTAB)
			get_all_symbols(symbols, f, (struct symtab_command*)lc);
		else if (f->is_64 && r32(&lc->cmd, f) == LC_SEGMENT_64)
			get_sections_64(sections, (struct segment_command_64*)lc, &j, f);
		else if (!f->is_64 && r32(&lc->cmd, f) == LC_SEGMENT)
			get_sections_32(sections, (struct segment_command*)lc, &j, f);
		lc = (void*)lc + r32(&lc->cmdsize, f);
		i++;
	}
}
