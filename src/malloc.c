/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:11:41 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/29 22:57:23 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		find_block(t_block allocation, t_block *last, size_t size)
{
	t_block	block;

	block = allocation;
	while (block && block->size <= size + BLOCK_SIZE && !block->free)
	{
		*last = block;
		block = block->next;
	}
	if (block)
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
	block->ptr = block->data;
	return (block);
}

t_block		new_allocation(t_block allocation, size_t size, size_t malloc_size)
{
	t_block block;
	t_block last;

	last = allocation;
	block = find_block(allocation, &last, size);
	if (block && (block->size - size) >= (BLOCK_SIZE + 4))
	{
		block = split_block(block, size);
		block->free = 0;
	}
	else
	{
		if (!(block = extend_heap(last, malloc_size)))
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
		if (size < TINY)
			global->tiny = allocation;
		else if (size < SMALL)
			global->small = allocation;
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
	block->ptr = &block->data;
	printf("%lu\n", block->size);
		// printf("%p\n", block);
	return (block->data);
}
