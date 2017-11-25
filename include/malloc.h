/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglandai <tglandai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:12:15 by tglandai          #+#    #+#             */
/*   Updated: 2017/11/25 22:53:55 by tglandai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

// # include "libft.h"

# define PAGE_SIZE getpagesize()
# define TINY (size_t)PAGE_SIZE * 2
# define SMALL (size_t)PAGE_SIZE * 8
# define BLOCK_SIZE sizeof(struct s_block)

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

typedef struct s_block *t_block;
typedef struct s_alloc *t_alloc;

struct			s_block {
	size_t		size;
	t_block		next;
	t_block		prev;
	int			free;
	char		data[1];
};

struct			s_alloc {
	t_block		tiny;
	t_block		small;
};
#endif
