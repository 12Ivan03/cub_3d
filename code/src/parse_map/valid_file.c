/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:33:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/14 11:01:48 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int valid_file_name(char *argv[])
{	
	char *c;
	
	c = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (c && c[4] == '\0')
		return (0);
	return (error_handler(2));
}

int	open_file(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_handler_msg(1, file));
	return (fd);
}

int	no_map(char *line)
{
	int i = 0;
	while (line[i])
	{
		
	}
	return 0
}

int	valid_direc_fc(int fd, t_game *game)
{
	// (void)fd;
	char *line;

	line = get_next_line(fd);
	while (line != NULL && no_map(line))
	{
		check_line(line, game);
			
		free(line);
		line = get_next_line(fd);
	}

	// came to map

	// eval the graph

	// if the grap is wrong 
	// clean 
	return 0;
}

int	valid_file_content(char *argv[], t_game *game) {

	int fd;

	fd = open_file(argv[1]);
	if (fd == -1)
		return (-1);
	// printf("here\n");
	valid_direc_fc(fd, game);
	// copy_map();
	// validate_map();
	close(fd);
	return 0;
}
