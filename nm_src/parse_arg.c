/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:01:35 by bandre            #+#    #+#             */
/*   Updated: 2018/05/30 20:39:53 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			get_file(t_mainstruct *file_struct, char *file_name)
{
	int			fd;
	struct stat	buff;
	void		*file;

	if ((fd = open(file_name, O_RDONLY)) <= 0)
	{
		file_struct->is_valid = -1;
		file_struct->error = "Invalid file";
		return ;
	}
	if (fstat(fd, &buff) < -1)
	{
		file_struct->is_valid = -1;
		file_struct->error = "Invalid file";
		return ;
	}
	if (!(file = (char*)malloc(buff.st_size + 2)))
	{
		file_struct->is_valid = 0;
		file_struct->error = "Malloc failed";
	}
	if (read(fd, file, buff.st_size) < buff.st_size)
	{
		file_struct->is_valid = -1;
		file_struct->error = "Invalid file";
		return ;
	}
	file_struct->file = file;
	file_struct->file[buff.st_size] = '\0';
	file_struct->file_length = buff.st_size;
}

void			initmainstruct(t_mainstruct *file)
{
	file->is_valid = 1;
	file->error = NULL;
	file->is_64 = -1;
	file->file_type = -1;
	file->bit_order = -1;
	file->file_length = -1;
	file->file = NULL;
	file->size_of_header = 0;
	file->nb_command = 0;
	file->filename = NULL;
}

t_mainstruct	*create_file(char *file)
{
	t_mainstruct *file_struct;

	file_struct = malloc(sizeof(t_mainstruct));
	if (!file_struct)
		return (NULL);
	initmainstruct(file_struct);
	get_file(file_struct, file);
	if (file_struct->is_valid == 0)
		return (NULL);
	get_type(file_struct);
	return (file_struct);
}
