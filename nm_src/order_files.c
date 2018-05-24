/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 19:13:01 by bandre            #+#    #+#             */
/*   Updated: 2018/05/24 15:08:26 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	order_f(
	t_libft_chained_list *maillon,
	void *params)
{
	t_mainstruct	*file1;
	t_mainstruct	*file2;
	void			*tmp;
	int				*yolo;
	int				*ended;

	yolo = (int*)params;
	ended = (int*)params;
	if (!maillon->next)
		return ;
	file1 = (t_mainstruct*)maillon->data;
	file2 = (t_mainstruct*)maillon->next->data;
	if (file1->file > file2->file)
	{
		*yolo = 1;
		tmp = maillon->data;
		maillon->data = maillon->next->data;
		maillon->next->data = tmp;
		*ended = 1;
	}
}

void	order_files(t_libft_chained_list **files)
{
	int		ended;

	ended = 1;
	while (ended == 1)
	{
		ended = 0;
		function_on_chained_list(files, order_f, &ended);
	}
}
