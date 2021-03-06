/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:30:15 by bandre            #+#    #+#             */
/*   Updated: 2018/06/20 17:40:40 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_putvoid(void *str)
{
	t_symbol *test;

	test = (t_symbol*)str;
	ft_printf("%016lx %s %d\n", test->value, test->name, (int)test->section);
}

void	get_type(t_mainstruct *file_struct)
{
	unsigned int	header;

	if (file_struct->file_length < (int)(sizeof(struct mach_header_64)))
	{
		file_struct->is_valid = 0;
		file_struct->error = "Invalid file";
		return ;
	}
	else
	{
		header = *(unsigned int*)file_struct->file;
		if (ft_strncmp("!<arch>\n", file_struct->file, 8) == 0)
			file_struct->file_type = 1;
		else if (FAT_MAGIC == header || FAT_MAGIC_64 == header
			|| FAT_CIGAM == header || FAT_CIGAM_64 == header)
		{
			file_struct->file_type = 2;
		}
		else
			file_struct->file_type = 0;
	}
}
