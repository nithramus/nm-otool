/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:52:50 by bandre            #+#    #+#             */
/*   Updated: 2018/05/24 14:44:11 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_putvoid(void *str)
{
	t_symbol *test;

	test = (t_symbol*)str;
	ft_printf("%016lx %s %d\n", test->value, test->name, (int)test->section);
}

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
		ft_putendl(file->error);
		return ;
	}
	order_symbol(&symbols);
	show_symbols(&symbols, &sections, file_struct);
}

void	parse_file(t_mainstruct *file_struct, char *filename)
{
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

int		main(int argc, char **argv)
{
	int				i;
	t_mainstruct	*file_struct;

	i = 1;
	if (argc < 2)
	{
		file_struct = create_file("a.out");
		parse_file(file_struct, "a.out");
	}
	else
	{
		while (i < argc)
		{
			file_struct = create_file(argv[i]);
			parse_file(file_struct, argv[i]);
			i++;
		}
	}
}
