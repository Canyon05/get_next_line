/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeh <ezeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:04:52 by ezeh              #+#    #+#             */
/*   Updated: 2024/02/14 10:09:13 by ezeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*last_line(char *raw)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		return (NULL);
	}
	while (raw[i] && raw[i] != '\n')
		i++;
	i++;
	while ((j < BUFFER_SIZE) && raw[i] && raw[i] != '\n')
		buffer[j++] = raw[i++];
	buffer[j++] = '\0';
	return (buffer);
}

void	polish_list(t_list **list)
{
	t_list	*final_note;
	t_list	*last_note;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last_note = find_last_note(*list);
	final_note = (void *)malloc(sizeof(t_list));
	if (final_note == NULL)
	{
		dealloc(list);
		return ;
	}
	final_note->buffer = last_line(last_note->buffer);
	if (final_note->buffer == NULL)
	{
		free(final_note);
		dealloc(list);
		return ;
	}
	final_note->next = NULL;
	dealloc(list);
	*list = final_note;
}

char	*ft_get_line(t_list *list)
{
	t_list	*current;
	char	*final_line;
	int		len;
	int		j;
	int		i;

	if (list == NULL)
		return (NULL);
	j = 0;
	len = count_len(list);
	final_line = (char *)malloc(len + 1);
	if (final_line == NULL)
		return (NULL);
	current = list;
	if (current == NULL)
		return (NULL);
	while (current != NULL)
	{
		i = 0;
		while ((j < (len - 1)) && current->buffer[i] && current->buffer[i] != '\n')
			final_line[j++] = current->buffer[i++];
		current = current->next;
	}
	final_line[j++] = '\n';
	final_line[j] = '\0';
	return (final_line);
}

t_list	*create_list(int fd, t_list *list)
{
	static t_list	*current;
	char	*string;
	int		charsread;

	current = list;
	while (!check_for_newline(current))
	{
		string = (char *)malloc(BUFFER_SIZE + 1);
		if (string == NULL)
			return (NULL);
		charsread = read(fd, string, BUFFER_SIZE);
		if (!charsread)
		{
			free(string);
			break ;
		}
		string[charsread] = '\0';
		add_note(&list, string);
		printf("Error >> create List\n");
	}
	return (list);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (NULL);
	list = create_list(fd, list); ///////
	printf("get LINE CALLLLLL\n");
	if (list == NULL)
		return (NULL);
	buffer = ft_get_line(list);
	polish_list(&list);
	return (buffer);
}
