/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:11:41 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/28 19:19:35 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		split_block(t_block block, size_t size)
{
	t_block	new;

	new = (t_block)(block->data + size);
	new->size = block->size - size - BLOCK_SIZE;
	new->next = block->next;
	new->free = 1;
	printf("%zu\n", size);
	block->next = new;
}

t_block		find_block(t_block allocation, t_block *last, size_t size)
{
	t_block	block;

	block = allocation;
	while (block && !(block->free && block->size >= size))
	{
		*last = block;
		block = block->next;
	}
	return (block);
}

t_block		extend_heap(t_block last, size_t size)
{
	t_block	block;

	if (!(block = mmap(0, size, PROT_READ | PROT_WRITE,
						MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (last)
		last->next = block;
	block->next = NULL;
	block->size = size;
	block->prev = last;
	block->free = 0;
	block->ptr = block->data;
	return (block);
}

t_block		new_allocation(t_block allocation, size_t size, size_t malloc_size)
{
	t_block block;
	t_block last;

	last = allocation;
	block = find_block(allocation, &last, size);
	if (block)
	{
		if ((block->size - size) >= (BLOCK_SIZE + 4))
			split_block(block, size);
		block->free = 0;
	}
	else
	{
		if (!(block = extend_heap(allocation, malloc_size)))
			return (NULL);
	}
	return (block);
}

t_block		allocate(t_block allocation, size_t size, size_t malloc_size)
{
	t_block block;

	block = NULL;
	if (!allocation)
	{
		if (!(allocation = extend_heap(NULL, malloc_size)))
			return (NULL);
		block = allocation;
	}
	else if (!(block = new_allocation(allocation, size, malloc_size)))
		return (NULL);
	return (block);
}

void		*malloc(size_t size)
{
	t_block			block;

	block = NULL;
	if (!global && !(global = mmap(0, sizeof(t_alloc),
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (size < TINY)
	{
		if (!(block = allocate(global->tiny, size, TINY)))
			return (NULL);
	}
	else if (size < SMALL)
	{
		if (!(block = allocate(global->small, size, SMALL)))
			return (NULL);
	}
	else
	{
		if (!(block = mmap(0, size, PROT_READ | PROT_WRITE,
							MAP_ANON | MAP_PRIVATE, -1, 0)))
			return (NULL);
		block->size = size;
	}
	printf("block %p\n", block);
	block->ptr = &block;
	return (block->data);
}
