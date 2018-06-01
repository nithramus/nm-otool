/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:52:50 by bandre            #+#    #+#             */
/*   Updated: 2018/06/01 19:02:46 by bandre           ###   ########.fr       */
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
		ft_printf("%s\n", file->error);
		return ;
	}
	create_symbol_list(&symbols, &sections, file);
	delete_chained_list(&symbols, free);
	delete_chained_list(&sections, free);
}

void	parse_file(t_mainstruct *file_struct, char *fname)
{
	if (file_struct->is_valid == 0)
		ft_putendl(file_struct->error);
	else if (file_struct->file_type == 0)
	{
		parse_header(file_struct);
		if (strcmp(file_struct->architecture, "ppc") == 0)
			ft_printf("%s (architecture %s):\n", fname,
				file_struct->architecture);
		else
			ft_printf("%s:\n", fname);
		print_file(file_struct);
	}
	else if (file_struct->file_type == 1)
	{
		ft_printf("%s : %s\n", "Archive : ", fname);
		archive(file_struct, fname);
	}
	else if (file_struct->file_type == 2)
		fat(file_struct, fname);
}

int		main(int argc, char **argv)
{
	int				i;
	t_mainstruct	*file_struct;
	int				retour;

	i = 1;
	retour = 0;
	if (argc < 2)
	{
		file_struct = create_file("a.out");
		if (!file_struct)
			return (1);
		parse_file(file_struct, "a.out");
		free(file_struct);
		free(file_struct->file);
	}
	else
		while (i < argc)
		{
			file_struct = create_file(argv[i]);
			if (!file_struct)
				return (1);
			parse_file(file_struct, argv[i]);
			if (file_struct->is_valid == 0)
				retour = 1;
			free(file_struct->file);
			free(file_struct);
			i++;
		}
	return (0);
}
