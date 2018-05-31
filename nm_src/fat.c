/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 20:32:16 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 12:51:01 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	set_fat_type(t_mainstruct *file_struct)
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
	file_struct->nb_command = reverse_32(&header.nfat_arch, file_struct);
	file_struct->file_type = 2;
}

void	ftofat(struct fat_arch *fat,
	void *file_ptr, t_mainstruct *main_file, char *file)
{
	t_mainstruct		file_struct;

	initmainstruct(&file_struct);
	file_struct.file_length = reverse(&fat->size, main_file);
	file_struct.file = file_ptr + reverse(&fat->offset, main_file);
	parse_header(&file_struct);
	if (strcmp(file_struct.architecture, "x86_64") != 0)
	{
		ft_printf("\n%s (for architecture %s):\n",
			file, file_struct.architecture);
	}
	print_file(&file_struct);
}

void	fat(t_mainstruct *f, char *file)
{
	struct fat_header	*header;
	unsigned int		i;
	int					offset;

	i = -1;
	offset = sizeof(struct fat_header);
	header = (struct fat_header*)f->file;
	set_fat_type(f);
	while (++i < f->nb_command)
	{
		if (reverse(f->file + offset, f) == CPU_TYPE_X86_64)
		{
			ftofat((struct fat_arch *)(f->file + offset), f->file, f, file);
			return ;
		}
		offset += f->size_of_header;
	}
	i = -1;
	offset = sizeof(struct fat_header);
	while (++i < f->nb_command)
	{
		ftofat((struct fat_arch *)(f->file + offset), f->file, f, file);
		offset += f->size_of_header;
	}
}
