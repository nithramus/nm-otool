/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:52:50 by bandre            #+#    #+#             */
/*   Updated: 2018/06/27 19:59:13 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_putsections(void *ptr)
{
	t_section *section;

	section = (t_section*)ptr;
	ft_putnbr(section->num);
	ft_putendl(section->sect_name);
}

void	print_file(void *file_struct)
{
	t_mainstruct			*file;
	t_libft_chained_list	*symbols;
	t_libft_chained_list	*sections;

	symbols = NULL;
	sections = NULL;
	file = (t_mainstruct*)file_struct;
	if (file->is_valid == 0)
	{
		ft_putendl(file->error);
		return ;
	}
	create_symbol_list(&symbols, &sections, file);
	if (file->is_valid == 0)
	{
		ft_printf("%s\n", file->error);
		return ;
	}
	order_symbol(&symbols);
	show_symbols(&symbols, &sections, file_struct);
}

void	parse_file(t_mainstruct *file_struct, char *filename)
{
	if (file_struct->is_valid == 0)
		ft_putendl(file_struct->error);
	if (file_struct->is_valid == 0)
		ft_putendl(file_struct->error);
	else if (file_struct->file_type == 0)
	{
		parse_header(file_struct);
		print_file(file_struct);
	}
	else if (file_struct->file_type == 1)
		archive(file_struct, filename);
	else if (file_struct->file_type == 2)
		fat(file_struct, filename);
}

int		yolo(char *file)
{
	t_mainstruct	*file_struct;
	int				retour;

	retour = 0;
	if (!(file_struct = create_file(file)))
		return (1);
	parse_file(file_struct, file);
	if (file_struct->is_valid == 0)
		retour = 1;
	free(file_struct->file);
	free(file_struct);
	return (retour);
}

int		main(int argc, char **argv)
{
	int				i;
	int				retour;

	i = 1;
	retour = 0;
	if (argc < 2 && (retour = 0))
	{
		if (yolo("a.out") != 0)
			retour = 1;
	}
	else
		while (i < argc)
		{
			if (yolo(argv[i]) != 0)
				retour = 1;
			i++;
		}
	return (retour);
}
