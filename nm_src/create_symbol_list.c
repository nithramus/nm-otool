/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_symbol_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:08:39 by bandre            #+#    #+#             */
/*   Updated: 2018/05/09 18:54:08 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_symbol	*create_t_symbol_32(t_libft_chained_list **symbols, void *ptr)
{
	//malloc
}

void	get_all_symbols(
	t_libft_chained_list **symbols,
	t_mainstruct *file,
	struct symtab_command *st)
{
	void	*stringable;
	void	*symtab;
	int		i;


	i = 0;
	stringable = (void*)st + reverse(st->stroff,4 ,file);
	symtab = (void*)st + reverse(st->symoff, 4, file);
	while (i < reverse(st->nsyms, 4, file))
	{
		// VERIFIER SYMTABSIZE
		add_back_maillon(symbols, symtab);
		if (file->is_64)
			symtab += sizeof(struct nlist_64);
		else
			symtab += sizeof(struct nlist);
		i++;
	}

}

void	create_symbol_list(t_libft_chained_list **symbols, t_mainstruct *file)
{
	struct load_command *lc;
	uint32_t			i;

	i = 0;
	lc = (struct load_command*)((void*)file + file->size_of_header);
	while (i < file->nb_command)
	{
		check_size_loadcmsg();
		if (reverse(lc->cmd, 4, file) == LC_SYMTAB)
		{
			ft_putendl("found the thing");
			get_all_symbols(symbols, file, lc);
		}
		lc = (void*)lc + reverse(lc->cmdsize, 4, file);
		i++;
	}
}