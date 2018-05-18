/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:37:30 by bandre            #+#    #+#             */
/*   Updated: 2018/05/18 16:39:46 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	get_header_executable(t_mainstruct *file_struct)
{
	struct mach_header_64	header;

	header = *(struct mach_header_64*)file_struct->file;
	if (header.magic == MH_MAGIC || header.magic == MH_MAGIC_64)
		file_struct->bit_order = 1;
	else if (header.magic == MH_CIGAM || header.magic == MH_MAGIC_64)
		file_struct->bit_order = 0;
	else
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid header1";
		return ;
	}
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
	else
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid header2";
		return ;
	}
	file_struct->nb_command = header.ncmds;
	file_struct->file_type = header.filetype;
}

void	parse_header(t_mainstruct *file_struct)
{
	if (file_struct->file_length < (int)(sizeof(struct mach_header_64)))
	{
		file_struct->is_valid = 0;
		file_struct->error = "File too short4";
		ft_putendl(file_struct->error);
		return ;
	}
	get_header_executable(file_struct);
}
