/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeh <ezeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:19:52 by ezeh              #+#    #+#             */
/*   Updated: 2024/02/20 13:35:50 by ezeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	main(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("ERROR opening file");
// 		return (0);
// 	}
// 	i = 1;
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("line %i: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR opening file");
		return (0);
	}
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	// while (line != NULL)
	// {
	// 	printf("line: %s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("=======\n");
	// }
	close(fd);
	return (0);
}