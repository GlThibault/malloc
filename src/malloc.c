/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:11:41 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/25 21:36:03 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		split_block(t_block block, size_t size)
{
	t_block	new;

	new = (t_block)(block->data + size);
	new->size = block->size - size - BLOCK_SIZE;
	new->next = block->next;
	new->free = 1;
	block->size = size;
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
	block->free = 0;
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
	static t_alloc	global = NULL;
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
	else if (!(block = mmap(0, size, PROT_READ | PROT_WRITE,
							MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	return (block->data);
}
