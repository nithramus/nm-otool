/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:54:58 by bandre            #+#    #+#             */
/*   Updated: 2018/05/10 19:27:03 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	get_sections_32(t_libft_chained_list **sections, t_mainstruct file)
{

}

void	get_sections_64(t_libft_chained_list **sections, struct segment_command_64 *lc)
{
	unsigned int		i;
	struct section_64	*sect;
	t_section			*section;

	i = 0;
	sect = (void*)lc + sizeof(struct segment_command_64);
	while (i < lc->nsects)
	{
		section = malloc(sizeof(t_section));
		ft_putendl(sect->sectname);
		ft_putendl(sect->segname);
		section->name = sect->sectname;
		section->num = i;
		add_back_maillon(sections, section);
		sect = (void*)sect + sizeof(struct section_64);
		i++;
	}
}