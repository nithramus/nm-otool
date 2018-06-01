/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:30:15 by bandre            #+#    #+#             */
/*   Updated: 2018/06/01 15:59:49 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	find_symbol(
	t_libft_chained_list *maillon,
	void *params)
{
	t_search_section	*search;
	t_section			*sect;

	sect = (t_section*)maillon->data;
	search = (t_search_section*)params;
	if (sect->num == search->value)
	{
		search->type = sect->sect_name;
	}
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
