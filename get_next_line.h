/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:40:08 by svikornv          #+#    #+#             */
/*   Updated: 2023/05/09 14:44:24 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 43
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_vars
{
	int		read_size;
	char		*buf;
	char		*line;
	t_list		*nl_node;
	int		nl_nodeth;
	int		nl_indx;
	int		node_count;
	int		node_len;
	int		total_len;
}			t_vars;

char	*get_next_line(int fd);
int		contain_nl(t_list *stash, t_vars *v);
void	free_stash(t_list **stash, t_vars *v);
void	add_to_stash(t_list **stash, t_vars *v);
char	*extract_line(t_list *stash, t_vars *v);
void	clear_list(t_list **list);
t_list	*generate_node(int i);
void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif
