/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:54:58 by bandre            #+#    #+#             */
/*   Updated: 2018/05/26 17:27:47 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_itoa2(unsigned char value, char ret[2])
{
	int div;

	div = value / 16;
	if (div >= 0 && div <= 9)
		ret[0] = div + '0';
	else
		ret[0] = div + 'a' - 10;
	div = value % 16;
	if (div >= 0 && div <= 9)
		ret[1] = div + '0';
	else
		ret[1] = div + 'a' - 10;
}

void	print_memory(char *addrchar, size_t size, uint64_t value, t_mainstruct *file_struct)
{
	size_t i;
	char ret[2];

	i = -1;
	ft_printf("%s:\n%s", file_struct->filename, "Contents of (__TEXT,__text) section");
	while (++i < size)
	{
		if ((i) % 16 == 0)
		{
			ft_putendl("");
			if (file_struct->is_64)
				ft_printf("%016llx\t",value + i);
			else
				ft_printf("%08lx\t",value + i);
		}
		ft_itoa2(addrchar[i], ret);		
		write(1, ret, 2);
		ft_putstr(" ");
	}
	ft_putendl("");
}

void	get_sections_32(
	t_libft_chained_list **sections,
	struct segment_command *lc,
	int *j,
	t_mainstruct *file_struct)
{
	int				i;
	struct section	*sect;
	t_section		*section;

	i = 0;
	sect = (void*)lc + sizeof(struct segment_command);
	while (i < (int)reverse_32(&lc->nsects, file_struct))
	{
		section = malloc(sizeof(t_section));
		if (!section)
		{
			file_struct->is_valid = 0;
			file_struct->error = "Malloc failed";
			return;
		}
		section->sect_name = sect->sectname;
		section->seg_name = sect->segname;
		section->num = *j;
		add_back_maillon(sections, section);
		sect = (void*)sect + sizeof(struct section);
		i++;
		(*j)++;
	}
}

void	get_sections_64(
	t_libft_chained_list **sections,
	struct segment_command_64 *lc,
	int *j,
	t_mainstruct *file_struct)
{
	int					i;
	struct section_64	*sect;
	t_section			*section;

	i = 0;
	sect = (void*)lc + sizeof(struct segment_command_64);
	while (i < (int)reverse_32(&lc->nsects, file_struct))
	{
		section = malloc(sizeof(t_section));
		if (!section)
		{
			file_struct->is_valid = 0;
			file_struct->error = "Malloc failed";
			return;
		}
		section->sect_name = sect->sectname;
		section->seg_name = sect->segname;
		section->num = *j;
		// TEST SIZE
		if (ft_strcmp(sect->sectname, "__text") == 0)
		{
			print_memory(file_struct->file + sect->offset, sect->size, sect->addr, file_struct);
			exit(0);
		}
		add_back_maillon(sections, section);
		sect = (void*)sect + sizeof(struct section_64);
		i++;
		(*j)++;
	}
}
