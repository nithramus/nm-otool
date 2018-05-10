/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:52:50 by bandre            #+#    #+#             */
/*   Updated: 2018/05/10 18:20:43 by bandre           ###   ########.fr       */
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
	ft_printf("%016lx %s\n", test->value, test->name);

}

void	print_file(void *file_struct)
{
	t_mainstruct *file;
	t_libft_chained_list	*symbols;
	t_libft_chained_list	*sections;

	symbols = NULL;
	file = (t_mainstruct*)file_struct;
	if (file->is_valid == 1)
		create_symbol_list(&symbols, &sections, file);
	if (file->is_valid)
		simple_function_on_chained_list(&symbols, ft_putvoid);
	show_symbols(&symbols, &sections, file_struct);
}

int	main(int argc, char **argv)
{
	t_libft_chained_list	*files;

	files = NULL;
	parse_arg(&files, argc, argv);
	ft_putendl("parsed");
	simple_function_on_chained_list(&files, print_file);
}