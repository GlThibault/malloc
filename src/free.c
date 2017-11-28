/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:25:40 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/28 19:06:49 by tglandai         ###   ########.fr       */
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
	t_block		block;

	block = global->tiny;
	printf("test\n");
	printf("%p\n", global->tiny);
	printf("%p\n", block->data);
	while (block && block->ptr != ptr)
	{
		block = block->next;
	printf("--%s\n", ptr);
	printf("--%s\n", block->ptr);
	printf("test\n");
	}
	if (block && block->ptr == ptr)
	printf("fdglkhdfk\n");
	return ((t_block)ptr);
}

void    free(void *ptr)
{
	t_block		block;
	if (!ptr || !global)
		return;

	block = get_block(ptr);

	printf("%p\n", ptr);
	printf("%p\n", block);
	printf("%zu\n", block->size);
	block->free = 1;
	printf("%d\n", munmap(&block, block->size));
}