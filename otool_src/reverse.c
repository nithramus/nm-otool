/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:20:04 by bandre            #+#    #+#             */
/*   Updated: 2018/05/31 16:58:07 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		swap_bytes(char *array, char *ptr, size_t size)
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
	char		array[2];
	uint16_t	divi;

	divi = 1;
	if (file_struct->bit_order == 0)
	{
		swap_bytes(array, ptr, 2);
		value = *(uint16_t*)array;
	}
	else
		value = *(uint16_t*)ptr;
	return (value);
}

uint32_t	r32(void *ptr, t_mainstruct *file_struct)
{
	uint32_t	value;
	char		array[4];
	uint32_t	divi;

	divi = 1;
	if (file_struct->bit_order == 0)
	{
		swap_bytes(array, ptr, 4);
		value = *(uint32_t*)array;
	}
	else
		value = *(uint32_t*)ptr;
	return (value);
}

uint64_t	reverse_64(void *ptr, t_mainstruct *file_struct)
{
	uint64_t	value;
	char		array[8];
	uint64_t	divi;

	divi = 1;
	if (file_struct->bit_order == 0)
	{
		swap_bytes(array, ptr, 8);
		value = *(uint64_t*)array;
	}
	else
		value = *(uint64_t*)ptr;
	return (value);
}

uint64_t	reverse(void *ptr, t_mainstruct *file_struct)
{
	if (file_struct->is_64)
		return (reverse_64(ptr, file_struct));
	else
		return (uint64_t)(r32(ptr, file_struct));
}
