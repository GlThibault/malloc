/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:25:40 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/29 22:51:02 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>
t_block		fusion(t_block block)
{
	if (block->next && block->next->free)
	{
		block->size += BLOCK_SIZE + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
	}
	return (block);
}

t_block		get_block(void *ptr)
{
	char *tmp;

	tmp = ptr;
	return (ptr = tmp - 40);
}

void    free(void *ptr)
{
	t_block		block;
	
	if (!ptr || !global)
		return;
	block = get_block(ptr);
	if (block)
	{
		printf("%p\n", block);
		printf("%lu\n", block->size);
	}
	block->free = 1;
	munmap(&block, block->size);
}