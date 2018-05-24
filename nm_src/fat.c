/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 20:32:16 by bandre            #+#    #+#             */
/*   Updated: 2018/05/24 14:46:58 by bandre           ###   ########.fr       */
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
		file_struct->error = "Invalid file";
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
		file_struct->error = "Invalid file";
		return ;
	}
	file_struct->nb_command = reverse_32(&header.nfat_arch, file_struct);
	file_struct->file_type = 2;
}                                    

void	create_filestruct_from_fat(struct fat_arch *fat, void *file_ptr, t_mainstruct *main_file, char *file)
{
	t_mainstruct		*file_struct;

	file_struct = malloc(sizeof(t_mainstruct));
	if (!file_struct)
		quit_clean("malloc error");
	initmainstruct(file_struct);
	file_struct->file_length = reverse(&fat->size, main_file);
	file_struct->file = file_ptr + reverse(&fat->offset, main_file);
	parse_header(file_struct);
	if (strcmp(file_struct->architecture, "x86_64") != 0)
		ft_printf("\n%s (for architecture %s):\n", file, file_struct->architecture);
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
		if (reverse(file_struct->file + offset, file_struct) == CPU_TYPE_X86_64)
		{
			create_filestruct_from_fat((struct fat_arch *)(file_struct->file + offset), file_struct->file, file_struct, file);
			return ;
		}
		offset += file_struct->size_of_header;
		i++;
	}
	i = 0;
	offset = sizeof(struct fat_header);
	while (i < file_struct->nb_command)
	{
		create_filestruct_from_fat((struct fat_arch *)(file_struct->file + offset), file_struct->file, file_struct, file);

		offset += file_struct->size_of_header;
		i++;
	}
}