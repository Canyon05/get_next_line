/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeh <ezeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:04:52 by ezeh              #+#    #+#             */
/*   Updated: 2024/02/14 14:35:50 by ezeh             ###   ########.fr       */
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
	buffer = (void *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		return (NULL);
	}
	while (raw[i] && raw[i] != '\n')
		i++;
	i++;
	while ((j < BUFFER_SIZE) && raw[i])
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
// void	polish_list(t_list **list)
// {

// 	dealloc(list);
// }

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
		if (current->buffer[i] == '\n')
			final_line[j++] = '\n';
		current = current->next;
	}
	final_line[j] = '\0';
	return (final_line);
}

t_list	*create_list(int fd, t_list **list)
{
	// static t_list	*list;
	char	*string;
	int		charsread;

	while (!check_for_newline(*list))
	{
		string = (char *)malloc(BUFFER_SIZE + 1);
		if (string == NULL)
			return (NULL);
		charsread = read(fd, string, BUFFER_SIZE);
		if (charsread < 0)
			return (dealloc(list), free(string), NULL);
		if (!charsread)
		{
			free(string);
			break ;
		}
		string[charsread] = '\0';
		add_note(list, string);
	}
	return (*list);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list = create_list(fd, &list); ///////
	if (list == NULL)
		return (NULL);
	buffer = ft_get_line(list);
	if (buffer[0] == '\0')
		return (free(buffer), dealloc(&list), NULL);
	polish_list(&list);
	return (buffer);
}


// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("ERROR opening file");
// 		return (0);
// 	}
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	// while (line != NULL)
// 	// {
// 	// 	printf("line: %s", line);
// 	// 	free(line);
// 	// 	line = get_next_line(fd);
// 	// 	printf("=======\n");
// 	// }
// 	close(fd);
// 	return (0);
// }

// void	dealloc(t_list **list)
// {
// 	t_list	*temp;

// 	while (*list)
// 	{
// 		temp = (*list)->next;
// 		free((*list)->buffer);
// 		free(*list);
// 		*list = temp;
// 	}
// 	*list = NULL;
// }

// int	count_len(t_list *list)
// {
// 	t_list	*current;
// 	int		len_n;
// 	int		len_c;

// 	len_n = 0;
// 	len_c = 0;
// 	if (list == NULL)
// 		return (0);
// 	current = list;
// 	while (current->next != NULL)
// 	{
// 		len_n++;
// 		current = current->next;
// 	}
// 	current = find_last_note(list);
// 	while (current->buffer[len_c] != '\n' && current->buffer[len_c])
// 		len_c++;
// 	len_c = ((len_c + 1) + (len_n * 10));
// 	return (len_c);
// }

// int	check_for_newline(t_list *list)
// {
// 	int	i;

// 	if (list == NULL)
// 		return (0);
// 	while (list != NULL)
// 	{
// 		i = 0;
// 		while (list->buffer[i] && i < BUFFER_SIZE)
// 		{
// 			if (list->buffer[i] == '\n')
// 				return (1);
// 			++i;
// 		}
// 		list = list->next;
// 	}
// 	return (0);
// }

// void	add_note(t_list **list, char *buffer)
// {
// 	t_list	*new_node;
// 	t_list	*last_node;

// 	last_node = find_last_note(*list);
// 	new_node = (void *)malloc(sizeof(t_list));
// 	if (new_node == NULL)
// 	{
// 		dealloc(list);
// 		return ;
// 	}
// 	if (last_node == NULL)
// 	{
// 		*list = new_node; 
// 	}
// 	else
// 	{
// 		last_node->next = new_node;
// 	}
// 	new_node->buffer = buffer;
// 	new_node->next = NULL;
// 	// print_list(*list);
// }


// void	*find_last_note(t_list *list)
// {
// 	if (list == NULL)
// 		return (NULL);
// 	while (list->next != NULL)
// 		list = list->next;
// 	return (list);
// }

