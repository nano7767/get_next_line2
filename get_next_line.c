/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:52 by svikornv          #+#    #+#             */
/*   Updated: 2023/05/05 14:19:09 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	contain_nl(t_list *stash)
{
	int			i;
	t_list		*ptr;

	ptr = stash;
	while (ptr)
	{
		i = 0;
		while (ptr->content[i])
			if (ptr->content[i++] == '\n')
				return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	free_stash(t_list **stash, t_list *ptr, int nl_pos)
{
	int	j;
	t_list		*tmp;

	tmp = generate_tmp(allnodelen(*stash) - ++nl_pos);
	j = 0;
	while (ptr)
	{
		while (ptr->content[nl_pos])
			tmp->content[j++] = ptr->content[nl_pos++];
		ptr = ptr->next;
		nl_pos = 0;
	}
	tmp->content[j] = '\0';
	clear_list(stash);
	*stash = tmp;
}
void	add_to_stash(t_list **stash, char *buf, int read_size)
{
	t_list	*ptr;
	t_list	*new_node;

	new_node = generate_tmp(read_size);
	buf[read_size] = '\0';
	new_node->content[read_size] = '\0';
	while (read_size--)
		new_node->content[read_size] = buf[read_size];
	free(buf);
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	ptr = *stash;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_node;
}

char	*extract_line(t_list **stash)
{
	char		*line;
	int			i;
	int			j;
	t_list		*ptr;

	i = 0;
	line = (char *)malloc(sizeof(char) * (allnodelen(*stash) + 1));
	if (!line)
		return (NULL);
	ptr = *stash;
	while (ptr)
	{
		j = 0;
		while (ptr->content[j])
		{
			if (ptr->content[j] == '\n')
			{	
				line[i++] = ptr->content[j];
				line[i] = '\0';
				free_stash(stash, ptr, j);
				return (line);
			}
			line[i++] = ptr->content[j++];
		}
		ptr = ptr->next;
	}
	line[i] = '\0';
	clear_list(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*buf;
	char			*line;
	int				read_size;

	while (contain_nl(stash) == 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		read_size = read(fd, buf, BUFFER_SIZE);
		if ((!stash && !read_size) || read_size == -1 || BUFFER_SIZE <= 0)
			return (free(buf), NULL);
		if (read_size == 0 && stash && contain_nl(stash) == 0)
		{
			free(buf);
			break ;
		}
		add_to_stash(&stash, buf, read_size);
	}
	line = extract_line(&stash);
	//free_stash(&stash);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
/*
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*status;

	fd = open("test.txt", O_RDONLY);
	while (status != NULL)
	{
		status = get_next_line(fd);
		printf("%s", status);
	}
}
*/
