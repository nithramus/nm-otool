/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:37:30 by bandre            #+#    #+#             */
/*   Updated: 2018/05/09 20:03:53 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	get_header(t_mainstruct *file_struct)
{
	struct mach_header_64	header;
	int						magic;

	header = *(struct mach_header_64*)file_struct->file;
	if (header.magic == MH_MAGIC || header.magic == MH_MAGIC_64)
	{
		file_struct->bit_order = 1;
	}
	else if (header.magic == MH_CIGAM || header.magic == MH_MAGIC_64)
	{
		file_struct->bit_order = 0;
	}
	else
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid header";
		return NULL;
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
		file_struct->error = "Invalid header";
		return NULL;
	}
	file_struct->nb_command = header.ncmds;
}

void	parse_header(t_mainstruct *file_struct)
{
	struct mach_header_64 header;

	if (file_struct->file_length < (sizeof(struct mach_header_64)))
	{
		file_struct->is_valid = 0;
		file_struct->error = "File too short";
		return ;
	}

	// 1/ test_header
	
}