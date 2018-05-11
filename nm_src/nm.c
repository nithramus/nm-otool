/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:52:50 by bandre            #+#    #+#             */
/*   Updated: 2018/05/11 13:10:31 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		ft_putvoid(void *str)
{
	t_symbol *test;

	test = (t_symbol*)str;
	// ft_putendl("");
	// ft_putnbr((int)test->section);
	// ft_putstr(" ");
	// ft_putendl(test->name);
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
	t_mainstruct *file;
	t_libft_chained_list	*symbols;
	t_libft_chained_list	*sections;

	symbols = NULL;
	sections = NULL;
	file = (t_mainstruct*)file_struct;
	if (file->is_valid == 1)
		create_symbol_list(&symbols, &sections, file);
	// simple_function_on_chained_list(&symbols, ft_putvoid);
	// simple_function_on_chained_list(&sections, ft_putsections);
	
	// ft_putendl("here");
	order_symbol(&symbols);
	show_symbols(&symbols, &sections, file_struct);
	// show_symbols(&symbols, &sections, file_struct);
}

int	main(int argc, char **argv)
{
	t_libft_chained_list	*files;

	files = NULL;
	parse_arg(&files, argc, argv);
	// ft_putendl("parsed");
	simple_function_on_chained_list(&files, print_file);
}