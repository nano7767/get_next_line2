/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:17 by svikornv          #+#    #+#             */
/*   Updated: 2023/05/09 14:43:47 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

t_list	*generate_node(int i)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->content = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp->content)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

void	clear_list(t_list **list)
{
	t_list	*current;
	t_list	*temp;

	current = *list;
	while (current)
	{
		free(current->content);
		temp = current->next;
		free(current);
		current = temp;
	}
	*list = NULL;
}

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dst;
	s = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
