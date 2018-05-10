/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:20:04 by bandre            #+#    #+#             */
/*   Updated: 2018/05/10 15:27:25 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	reverse(void *ptr, size_t size, t_mainstruct *file)
{
	uint32_t *test;
	
	test = (uint32_t*)ptr;
	size += 1-1;
	file += 1-1;
	return *test;
}