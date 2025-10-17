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

int	valid_direc_fc(int fd, t_game **game)
{
	// (void)fd;
	(void)game;
	char *line;

	// printf("2\n");
	line = get_next_line(fd);

	printf("one: %s\n", line);
	while (line != NULL)
	{
		if (check_line(line, game) == -1)
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
		printf("loop line : %s\n", line);
	}
	// 1. eval the graph is correct!
	if (eval_graph(game))
		return(free(line), -1);
	// 2. continue reading file for map;
	// while(line != NULL)
	// {
	// 	//parse maps
	// }
	//3. eval if map is currect;
	
	return 0;
}

int	valid_file_content(char *argv[], t_game **game) {

	int fd;

	fd = open_file(argv[1]);
	if (fd == -1)
		return (-1);
	// printf("here\n");
	if (valid_direc_fc(fd, game))
		return (close(fd), 1);
	// copy_map();
	// validate_map();
	close(fd);
	return 0;
}
