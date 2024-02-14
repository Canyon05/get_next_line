/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeh <ezeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:35:22 by ezeh              #+#    #+#             */
/*   Updated: 2024/02/14 09:57:06 by ezeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dealloc(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->buffer);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

int	count_len(t_list *list)
{
	t_list	*current;
	int		len_n;
	int		len_c;

	len_n = 0;
	len_c = 0;
	if (list == NULL)
		return (0);
	current = list;
	while (current->next != NULL)
	{
		len_n++;
		current = current->next;
	}
	current = find_last_note(list);
	while (current->buffer[len_c] != '\n' && current->buffer[len_c])
		len_c++;
	len_c = ((len_c + 1) + (len_n * 10));
	return (len_c);
}

int	check_for_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	i = 0;
	while (list->buffer[i] && i < BUFFER_SIZE)
	{
		if (list->buffer[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

void	add_note(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	print_list(*list);
	last_node = find_last_note(*list);
	printf("ERROR > add_note\n");
	new_node = (void *)malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		dealloc(list);
		return ;
	}
	if (last_node == NULL)
	{
		*list = new_node; 
	}
	else
	{
		last_node->next = new_node;
	}
	new_node->buffer = buffer;
	new_node->next = NULL;
	// print_list(*list);
}

void	print_list(t_list *list)
{
	t_list	*current;
	current = list;
	printf("xxx\n");
	while (current)
	{
		printf("%s\n", current->buffer);
		current = current->next;
	}
	printf("xxx\n");	
}

void	*find_last_note(t_list *list)
{
	t_list	*current;

	current = list;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}
