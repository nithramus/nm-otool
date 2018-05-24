/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 11:50:49 by bandre            #+#    #+#             */
/*   Updated: 2018/05/24 15:57:16 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	file_done(
	t_libft_chained_list *maillon,
	void *param)
{
	t_search		*search;
	t_mainstruct	*file_struct;

	search = (t_search*)param;
	file_struct = (t_mainstruct *)maillon->data;
	if (file_struct->file == search->searched)
		search->found = 1;
}

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

void	create_file_from_archive(
	struct ar_hdr *ar,
	t_libft_chained_list **first,
	char *file)
{
	t_search		search;
	t_mainstruct	*file_struct;
	char			*name;

	search.searched = ((void*)ar) + header_name(ar, &name);
	search.found = 0;
	function_on_chained_list(first, file_done, (void*)&search);
	if (search.found == 1)
		return ;
	file_struct = malloc(sizeof(t_mainstruct));
	if (!file_struct)
		quit_clean("yoloswag");
	initmainstruct(file_struct);
	file_struct->file = ((void*)ar) + header_name(ar, &name);
	file_struct->file_length = ft_atoi(ar->ar_size);
	file_struct->filename = name;
	add_back_maillon(first, file_struct);
}

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
			quit_clean("malloc failed");
		*name = ptr + size;
		ft_strcpy(*name, ptr + size);
		size += ft_atoi(header->ar_name + 3);
	}
	else
	{
		if (!(*name = malloc(20)))
			quit_clean("malloc failed");
		ft_strncpy(*name, header->ar_name, 16);
		(*name)[16] = '\0';
		pos = ft_strrchr(*name, 20);
		if (pos)
			*pos = '\0';
	}
	return (size);
}

void	archive(t_mainstruct *file_struct, char *file)
{
	t_libft_chained_list	*file_list;
	int						offset;
	int						size;
	char					*name;
	struct ranlib			*ran;

	offset = 8;
	file_list = NULL;
	offset += header_name(file_struct->file + offset, &name);
	size = *(int*)(file_struct->file + offset);
	offset += sizeof(int);
	while (size > 0)
	{
		ran = (struct ranlib*)((void*)file_struct->file + offset);
		create_file_from_archive((struct ar_hdr*)((void*)file_struct->file
			+ ran->ran_off), &file_list, file);
		offset += sizeof(struct ranlib);
		size -= sizeof(struct ranlib);
	}
	order_files(&file_list);
	function_on_chained_list(&file_list, show_all_files, file);
}
