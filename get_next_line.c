/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:02:52 by svikornv          #+#    #+#             */
/*   Updated: 2023/05/09 15:38:22 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_vars(t_vars *v)
{
	v->buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!v->buf)
		return ;
	v->buf[0] = '\0';
	v->line = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!v->line)
	{
		free(v->buf);
		return ;
	}
	v->line[0] = '\0';
	v->nl_node = NULL;
	v->nl_nodeth = 0;
	v->nl_indx = -1;
	v->node_count = 0;
	v->node_len = 0;
	v->total_len = 0;
}

void	add_to_stash(t_list **stash, t_vars *v)
{
	int	i;
	t_list *new_node;
	t_list	*ptr;
	
	new_node = generate_node(v->read_size);
	if (!new_node)
		return ;
	ft_memcpy(new_node->content, v->buf, v->read_size);
	new_node->content[v->read_size] = '\0';
	ptr = *stash;
	if (!*stash)
	{
		*stash = new_node;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_node;
	v->node_count++;
}

int	contain_nl(t_list *stash, t_vars *v)
{
	int		i;
	t_list		*ptr;

	ptr = stash;
	while (ptr)
	{
		i = 0;
		while (ptr->content[i])
			if (ptr->content[i++] == '\n')
			{
				v->nl_node = ptr;
				v->nl_indx = i;
				return (1);
			}
		ptr = ptr->next;
		v->nl_nodeth++;
	}
	return (0);
}

char	*extract_line(t_list *stash, t_vars *v)
{
	int		i;
	int		j;
	char	*line;
	t_list	*ptr;

	if (v->read_size != BUFFER_SIZE)
		v->node_len = v->read_size;
	v->total_len = (BUFFER_SIZE * v->node_count - 1) + v->node_len;
	line = (char *)malloc(sizeof(char) * (v->total_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	ptr = stash;
	while (ptr)
	{
		j = 0;
		while (ptr->content[j] && ptr->content[j] != '\n')
			line[i++] = ptr->content[j++];
		if (ptr->content[j] == '\n')
		{
			line[i++] = '\n';
			break;
		}
		ptr = ptr->next;
	}
	line[i] = '\0';
	return (line);
}

void	free_stash(t_list **stash, t_vars *v)
{
	t_list	*tmp;
	t_list	*ptr;
	int	i;
	int	j;

	i = v->nl_indx;
	if (v->nl_indx == -1)
	{
		clear_list(stash);
		return ;
	}
	tmp = generate_node(v->total_len - ((v->nl_nodeth - 1) * BUFFER_SIZE) + v->nl_indx + 1);
	if (!tmp)
		return ;
	ptr = *stash;
	j = 0;
	while (ptr)
	{
		while (ptr->content[i])
			tmp->content[j++] = ptr->content[i++];
		ptr = ptr->next;
		i = 0;
	}
	tmp->content[j] = '\0';
	clear_list(stash);
	*stash = tmp;
	(*stash)->next = NULL;
	v->node_count -= v->nl_nodeth;
	v->node_len = v->total_len - ((v->node_count - 1) * BUFFER_SIZE);
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	t_vars	v;
	char		*line;

	init_vars(&v);
	while (contain_nl(stash, &v) == 0)
	{
		v.read_size = read(fd, v.buf, BUFFER_SIZE);
		if ((!stash && !v.read_size) || v.read_size == -1 || BUFFER_SIZE <= 0)
			return (free(v.buf), free(v.line), NULL);
		if (v.read_size == 0 && stash && contain_nl(stash, &v) == 0)
		{
			free(v.buf);
			break ;
		}
		add_to_stash(&stash, &v);
	}
	line = extract_line(stash, &v);
	if (!line)
		return (NULL);
	free_stash(&stash, &v);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);		
}

#include <fcntl.h>
int	main(void)
{
	int	fd;
	char	*s;

	fd = open("test.txt", O_RDONLY);
	while (s != NULL)
	{
		s = get_next_line(fd);
		printf("%s", s);
	}
}
