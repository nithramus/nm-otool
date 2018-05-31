/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maillon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:02:26 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 19:06:52 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

t_libft_chained_list	*create_maillon(t_libft_chained_list *next,
	t_libft_chained_list *before, void *data)
{
	t_libft_chained_list *maillon;

	maillon = (t_libft_chained_list*)malloc(sizeof(t_libft_chained_list));
	if (!maillon)
	{
		ft_puterror("Failed to create maillon\n");
		return (NULL);
	}
	maillon->next = next;
	maillon->before = before;
	maillon->data = data;
	return (maillon);
}
