/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:20:04 by bandre            #+#    #+#             */
/*   Updated: 2018/05/23 19:51:19 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	swap(char *array, char *ptr, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		array[i] = ptr[size - i - 1];
		i++;
	}
}

uint16_t	reverse_16(void *ptr, t_mainstruct *file_struct)
{
	uint16_t	value;
	char		*array;
	uint16_t	divi;

	divi = 1;
	if (file_struct->bit_order == 0)
	{
		array = ft_memalloc(16);
		if (!array)
			quit_clean("Malloc failed");
		swap(array, ptr, 2);
		value = *(uint16_t*)array;
	}
	else
		value = *(uint16_t*)ptr;
	return (value);
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
		swap(array, ptr, 4);
		value = *(uint32_t*)array;
	}
	else
		value = *(uint32_t*)ptr;

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
		swap(array, ptr, 8);
		value = *(uint64_t*)array;
	}
	else
		value = *(uint64_t*)ptr;
	// size += 1 - 1;
	// file += 1 - 1;
	return (value);
}