/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:20:04 by bandre            #+#    #+#             */
/*   Updated: 2018/05/22 16:40:14 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint32_t	swap(char *array, char *ptr, size_t size)
{
	size_t i;
	uint32_t value;

	i = 0;
	while (i < size)
	{
		array[i] = ptr[size - i - 1];
		i++;
	}
	value = *(uint32_t*)array;
	return value;
}

uint32_t	reverse_32(void *ptr, t_mainstruct *file_struct)
{
	uint32_t	value;
	char		*array;
	uint32_t	divi;

	divi = 1;
	if (file_struct->bit_order == 0)
	{
		array = ft_memalloc(32);
		if (!array)
			quit_clean("Malloc failed");
		return (swap(array, ptr, 4));
	}
	else
		value = *(uint32_t*)ptr;
	// size += 1 - 1;
	// file += 1 - 1;
	return (value);
}

uint64_t	reverse_64(void *ptr, t_mainstruct *file_struct)
{
	uint64_t	value;
	char		*array;
	uint64_t	divi;

	divi = 1;
	if (file_struct->bit_order == 0)
	{
		array = ft_memalloc(64);
		if (!array)
			quit_clean("Malloc failed");
		return (swap(array, ptr, 8));
	}
	else
		value = *(uint64_t*)ptr;
	// size += 1 - 1;
	// file += 1 - 1;
	return (value);
}