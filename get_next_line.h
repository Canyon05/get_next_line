/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeh <ezeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:05:11 by ezeh              #+#    #+#             */
/*   Updated: 2024/02/14 10:02:28 by ezeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
t_list	*create_list(int fd, t_list *list);
char	*polish_last_line(t_list *list);
void	polish_list(t_list **list);

void	dealloc(t_list **list);
int		count_len(t_list *list);
int		check_for_newline(t_list *list);
void	add_note(t_list **list, char *buffer);
void	*find_last_note(t_list *list);

void	print_list(t_list *list);

#endif