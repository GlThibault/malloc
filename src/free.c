/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:25:40 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/25 21:42:17 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	check_valid(void *ptr)
{
	ptr = ptr;
	return(1);
}

void    free(void *ptr)
{
	t_block		block;
	if (check_valid(ptr))
};