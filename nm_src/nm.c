/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:52:50 by bandre            #+#    #+#             */
/*   Updated: 2018/05/09 19:06:42 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_file(void *file_struct)
{
	t_mainstruct *file;
	t_libft_chained_list	*symbols;

	symbols = NULL;
	file = (t_mainstruct*)file_struct;
	if (file->is_valid == 1)	
		create_symbol_list(&symbols, file);
	else
		show_file(file);
}

int	main(int argc, char **argv)
{
	t_libft_chained_list	*files;

	files = NULL;
	parse_arg(&files, argc, argv);
	simple_function_on_chained_list(&files, print_file);

}