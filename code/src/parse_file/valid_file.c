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

int valid_file_name(char *argv, char *str)
{	
	char *c;

	c = ft_strnstr(argv, str, ft_strlen(argv));
	if (c && c[ft_strlen(str)] == '\0')
		return (0);
	return (1);
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
	char	*line;
	int		check;

	line = get_next_line(fd);
	// printf("First line: %s", line);
	while (line != NULL)
	{
		check = check_line(line, game);
		if (check == 1)
			return (free(line), 1);
		else if (check == 2)
			break;
		free(line);
		line = get_next_line(fd);
		// printf("loop line : %s", line);
	}
	if (check != 2)
		return (error_handler(2));

	if (eval_graph(game))
		return(free(line), 1);

	copy_map_to_game_struct(game, &line, fd);
	
	return 0;
}

int	eval_cell(t_game **game, int x, int y, int dx, int dy)
{
	if ((y == 0 || x == 0) && (*game)->map[x][y] == '0')
		return (1);
	if (dx == 1)
		if ((x > 0) && (*game)->map[x][y] == '0')
			if ((*game)->map[x - dx][y - dy] == ' ' || x == (*game)->height - 1)
				return (1);
	if (dy == 1)
		if (y > 0 && (*game)->map[x][y] == '0')
			if ((*game)->map[x - dx][y - dy] == ' ' || \
				(*game)->map[x + dx][y + dy] == ' ' || \
				(*game)->map[x + dx][y + dy] == '\0')
				return (1);
	return (0);
}

int	validate_map(t_game **game)
{
	int i; 
	int j;

	i = 0;
	while (i < (*game)->height)
	{
		j = 0;
		while (j < (*game)->width)
		{
			if (eval_cell(game, i, j, 0, 1))
				return (1);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < (*game)->width)
	{
		j = 0;
		while (j < (*game)->height)
		{
			if (eval_cell(game, j, i, 1, 0))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
// printf("H: %d, W: %d", (*game)->height, (*game)->width);
int	validate_struct(t_game **game)
{
	if ((*game)->player.position.x == -1)// || (*game)->player.position.y == -1)
		return (error_handler_msg(5, "a player"));
	if ((*game)->graph->C.rgb[0] == -1 || (*game)->graph->F.rgb[0] == -1)
		return (error_handler_msg(5, "colors"));
	return (0);
}

int	read_file_content(char *argv[], t_game **game) {

	int fd;

	fd = open_file(argv[1]);
	// printf("error here1\n");
	if (fd == -1)
		return (1);

	if (valid_direc_fc(fd, game))
		return (close(fd), 1);
	close(fd);
		// printf("error her2e\n");

	if (handle_map(game)) {
		// printf("error here3\n");	
		return (1);
	}
	if (validate_struct(game)){
		// printf("error here34\n");
		return (1);
	}
	
	if (validate_map(game))
		return (error_handler(5));


	return (0);
}
