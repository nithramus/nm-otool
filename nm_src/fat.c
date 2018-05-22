/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 20:32:16 by bandre            #+#    #+#             */
/*   Updated: 2018/05/18 17:35:17 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	set_fat_type(t_mainstruct *file_struct, uint32_t magic)
{
	struct fat_header	header;

	header = *(struct fat_header*)file_struct->file;
	if (header.magic == FAT_MAGIC || header.magic == FAT_MAGIC_64)
		file_struct->bit_order = 1;
	else if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64)
		file_struct->bit_order = 0;
	else
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid header1";
		return ;
	}
	if (header.magic == FAT_MAGIC || header.magic == FAT_CIGAM)
	{
		file_struct->size_of_header = sizeof(struct fat_arch);
		file_struct->is_64 = 0;
	}
	else if (header.magic == FAT_MAGIC_64 || header.magic == FAT_CIGAM_64)
	{
		file_struct->size_of_header = sizeof(struct fat_arch_64);
		file_struct->is_64 = 1;
	}
	else
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid header6";
		return ;
	}
	file_struct->nb_command = reverse_32(&header.nfat_arch, file_struct);
	file_struct->file_type = 2;
}

void	create_filestruct_from_fat(struct fat_arch *fat, void *file_ptr, t_mainstruct *main_file)
{
	t_mainstruct		*file_struct;

	file_struct = malloc(sizeof(t_mainstruct));
	initmainstruct(file_struct);
	file_struct->file_length = reverse_32(&fat->size, main_file);
	// ft_printf("%u", file_struct->file_length);
	file_struct->file = file_ptr + reverse_32(&fat->offset, main_file);
	// ft_putendl("coucou");
	parse_header(file_struct);
	print_file(file_struct);


}

void	fat(t_mainstruct *file_struct, char *file)
{
	struct fat_header	*header;
	unsigned int		i;
	int					offset;

	// test file_size
	i = 0;
	offset = sizeof(struct fat_header);
	header = (struct fat_header*)file_struct->file;
	set_fat_type(file_struct, header->magic);
	if (file_struct->is_valid == 0)
	{
		ft_putendl(file_struct->error);
		return ;
	}
	while (i < file_struct->nb_command)
	{
		if (reverse_32(file_struct->file + offset, file_struct) == CPU_TYPE_X86_64)
		{
			create_filestruct_from_fat((struct fat_arch *)(file_struct->file + offset), file_struct->file, file_struct);
			return ;
		}
		offset += file_struct->size_of_header;
		i++;
	}
	i = 0;
	offset = sizeof(struct fat_header);
	while (i < file_struct->nb_command)
	{
		// ft_printf("%u", file_struct->nb_command);
		// ft_putendl("coucou");
		create_filestruct_from_fat((struct fat_arch *)(file_struct->file + offset), file_struct->file, file_struct);

		offset += file_struct->size_of_header;
		i++;
		// check size

	}
}