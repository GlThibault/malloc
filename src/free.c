/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:25:40 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/25 23:08:28 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>
t_block		get_block(void *ptr)
{
	char	*tmp;

	tmp = ptr;
	printf("%s\n", tmp);
	return (ptr = tmp -= BLOCK_SIZE);
}

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

void    free(void *ptr)
{
	t_block		block;

	block = get_block(ptr);
	printf("%p\n", block);
	block->free = 1;
	if (block->prev && block->prev->free)
		block = fusion(block->prev);
	printf("1\n");
	if (block->next)
		fusion(block);
	else
	{
		if (block->prev)
			block->prev->next = NULL;
		else
			block = NULL;
		munmap(&block->data, block->size);
	}
};