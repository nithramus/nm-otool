/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:30:15 by bandre            #+#    #+#             */
/*   Updated: 2018/05/16 14:27:21 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	get_type(t_mainstruct *file_struct)
{
	if (file_struct->file_length < (int)(sizeof(struct mach_header_64)))
	{
		file_struct->is_valid = 0;
		file_struct->error = "File too short";
		return ;
	}
	else
	{
		if (ft_strncmp("!<arch>\n", file_struct->file, 8) == 0)
		{
			file_struct->file_type = 1;
		}
		else if (ft_strncmp("fat", file_struct->file, 3) == 0)
		{
			file_struct->file_type = 2;
		}
		else
		{
			file_struct->file_type = 0;			
		}
	}
}