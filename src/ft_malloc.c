/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 22:07:28 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/29 22:56:09 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
t_block		split_block(t_block block, size_t size)
{
	t_block	new;

	new = (t_block)(block->data + size);
	new->size = block->size - size - BLOCK_SIZE;
	new->next = block->next;
	new->free = 1;
	block->next = new;
	block->free = 0;
	return (new);
}
