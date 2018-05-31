/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:09:17 by bandre            #+#    #+#             */
/*   Updated: 2018/05/02 19:09:55 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_chained_list.h"

void	ft_puterror(char *error_message)
{
	int i;

	i = 0;
	while (error_message[i])
	{
		i++;
	}
	i = write(2, error_message, i);
	i = write(2, "\n", 1);
}
