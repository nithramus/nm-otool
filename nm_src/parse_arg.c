/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:01:35 by bandre            #+#    #+#             */
/*   Updated: 2018/05/16 19:07:41 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	get_file(t_mainstruct *file_struct, char *file_name)
{
	int fd;
	struct stat buff;
	void *file;

	if ((fd = open(file_name, O_RDONLY)) <= 0)
	{
		file_struct->is_valid = -1;
		file_struct->error = "Unable to open file";
		return ;
	}
	if (fstat(fd, &buff) < -1)
	{
		file_struct->is_valid = -1;
		file_struct->error = "Stat failed";
		return ;
	}
	if (!(file = (char*)malloc(buff.st_size + 1)))
	{
		file_struct->is_valid = -1;
		file_struct->error = "Malloc failed";
		return ;
	}
	if (read(fd, file, buff.st_size) < buff.st_size)
	{
		file_struct->is_valid = -1;
		file_struct->error = "Read fail";
		return ;
	}
	file_struct->file = file;
	file_struct->file_length = buff.st_size;
}

void	initmainstruct(t_mainstruct *file)
{
	file->is_valid = 1;
	file->error = NULL;
	file->is_64 = -1;
	file->file_type = -1;
	file->bit_order = -1;
	file->file_length = -1;
	file->file = NULL;
	file->size_of_header = 0;
	file->nb_command = -1;
	file->filename = NULL;
}



t_mainstruct	*create_file(t_libft_chained_list **first, char *file)
{
	t_mainstruct *file_struct;

	file_struct = malloc(sizeof(t_mainstruct));
	if (!file_struct)
		quit_clean();
	initmainstruct(file_struct);
	get_file(file_struct, file);
	get_type(file_struct);
	if (!file_struct->is_valid)
		return NULL;
	return (file_struct);
	// add_back_maillon(first, file_struct);
}

void	parse_arg(t_libft_chained_list **first, int argc, char **argv)
{
	int	i;
	t_mainstruct *file_struct;

	i = 1;
	if (argc < 2)
		create_file(first, "a.out");
	else
	{
		while (i < argc)
		{
			file_struct = create_file(first, argv[i]);
			if (file_struct->file_type == 0)
			{
				parse_header(file_struct);
				print_file(file_struct);
			}
			else if (file_struct->file_type == 1)
				archive(file_struct, argv[i]);
			i++;
		}
	}
}