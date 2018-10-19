/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:37:30 by bandre            #+#    #+#             */
/*   Updated: 2018/06/01 16:27:36 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		header_name(void *ptr, char **name)
{
	struct ar_hdr	*header;
	int				size;
	char			*pos;

	size = sizeof(struct ar_hdr);
	header = (struct ar_hdr*)ptr;
	if (ft_strncmp(header->ar_name, "#1/", 3) == 0)
	{
		if (!(*name = malloc(ft_atoi(header->ar_name + 3))))
			return (0);
		ft_strcpy(*name, ptr + size);
		size += ft_atoi(header->ar_name + 3);
	}
	else
	{
		if (!(*name = malloc(20)))
			return (0);
		ft_strncpy(*name, header->ar_name, 16);
		(*name)[16] = '\0';
		pos = ft_strrchr(*name, 20);
		if (pos)
			*pos = '\0';
	}
	return (size);
}

void	get_header_executable(t_mainstruct *file_struct)
{
	struct mach_header_64	header;
	const NXArchInfo		*info;

	header = *(struct mach_header_64*)file_struct->file;
	if (header.magic == MH_MAGIC || header.magic == MH_CIGAM)
	{
		file_struct->size_of_header = sizeof(struct mach_header);
		file_struct->is_64 = 0;
	}
	else if (header.magic == MH_MAGIC_64 || header.magic == MH_CIGAM_64)
	{
		file_struct->size_of_header = sizeof(struct mach_header_64);
		file_struct->is_64 = 1;
	}
	file_struct->nb_command = r32(&header.ncmds, file_struct);
	info = NXGetArchInfoFromCpuType(r32(&header.cputype, file_struct),
		r32(&header.cpusubtype, file_struct));
	if (info && info->name)
		file_struct->architecture = (char*)info->name;
}

void	parse_header(t_mainstruct *file_struct)
{
	struct mach_header_64	header;

	if (file_struct->file_length < (int)(sizeof(struct mach_header_64)))
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid file";
		return ;
	}
	header = *(struct mach_header_64*)file_struct->file;
	if (header.magic == MH_MAGIC || header.magic == MH_MAGIC_64)
		file_struct->bit_order = 1;
	else if (header.magic == MH_CIGAM || header.magic == MH_MAGIC_64)
		file_struct->bit_order = 0;
	else
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid file";
		return ;
	}
	get_header_executable(file_struct);
}
