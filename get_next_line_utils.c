/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:17 by svikornv          #+#    #+#             */
/*   Updated: 2023/05/05 14:29:53 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

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

int	allnodelen(t_list *lst)
{
	int		i;
	int		len;
	t_list	*ptr;

	ptr = lst;
	len = 0;
	while (ptr)
	{	
		i = 0;
		while (ptr->content[i])
		{
			i++;
			len++;
		}
		ptr = ptr->next;
	}
	return (len);
}

t_list	*generate_tmp(int i)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->content = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp->content == NULL)
		return (NULL);
	return (tmp);
}
/*
int	advance_to_nl(t_list **ptr)
{
	int	i;

	i = 0;
	while ((*ptr) && (*ptr)->content[i] != '\n')
	{
		if ((*ptr)->content[i] == '\0')
		{
			(*ptr) = (*ptr)->next;
			i = -1;
		}
		i++;
	}
	if (ptr == NULL)
		return (-1);
	return (i);
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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if ((d == s || len == 0))
		return (dst);
	if (d > s && s + len > d)
	{
		while (len--)
			d[len] = s[len];
	}
	else
		return (ft_memcpy(d, s, len));
	return (d);
}
*/
