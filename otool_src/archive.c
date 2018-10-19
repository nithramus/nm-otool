/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:50:49 by bandre            #+#    #+#             */
/*   Updated: 2018/06/27 20:01:53 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	show_all_files(
	t_libft_chained_list *maillon,
	void *param)
{
	t_mainstruct	*file_struct;

	file_struct = (t_mainstruct *)maillon->data;
	parse_header(file_struct);
	ft_printf("\n%s(%s):\n", param, file_struct->filename);
	print_file(file_struct);
}

int		create_file_from_archive(
	struct ar_hdr *ar,
	t_libft_chained_list **first)
{
	t_search		search;
	t_mainstruct	*file_struct;
	char			*name;

	search.searched = ((void*)ar) + header_name(ar, &name);
	if (!name)
		return (0);
	free(name);
	search.found = 0;
	function_on_chained_list(first, file_done, (void*)&search);
	if (search.found == 1)
		return (1);
	file_struct = malloc(sizeof(t_mainstruct));
	if (!file_struct)
		return (0);
	initmainstruct(file_struct);
	file_struct->file = ((void*)ar) + header_name(ar, &name);
	if (!name)
		return (0);
	file_struct->file_length = ft_atoi(ar->ar_size);
	file_struct->filename = name;
	add_back_maillon(first, file_struct);
	return (1);
}

void	delete_archive(void *file)
{
	t_mainstruct *file_struct;

	file_struct = (t_mainstruct*)file;
	free(file_struct->filename);
	free(file);
}

void	action(t_libft_chained_list *file_list, char *file)
{
	order_files(&file_list);
	function_on_chained_list(&file_list, show_all_files, file);
	delete_chained_list(&file_list, delete_archive);
}

void	archive(t_mainstruct *fs, char *file)
{
	t_libft_chained_list	*file_list;
	int						offset;
	int						size;
	char					*name;
	struct ranlib			*ran;

	offset = 8 + header_name(fs->file + 8, &name);
	if (!name && (file_list = NULL))
		return ;
	free(name);
	size = *(int*)(fs->file + offset);
	offset += sizeof(int);
	if ((void*)fs->file + size >= (void*)fs->file + fs->file_length)
		return ;
	while (size > 0 && (ran = (struct ranlib*)((void*)fs->file + offset)))
	{
		if ((void*)fs->file + ran->ran_off >= (void*)fs->file + fs->file_length)
			return ;
		if ((create_file_from_archive((struct ar_hdr*)((void*)fs->file
			+ ran->ran_off), &file_list)) == 0)
			return ;
		offset += sizeof(struct ranlib);
		size -= sizeof(struct ranlib);
	}
	action(file_list, file);
}
