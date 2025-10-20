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

int valid_file_name(char *argv[], char *str)
{	
	char *c;
	
	c = ft_strnstr(argv[1], str, ft_strlen(argv[1]));
	if (c && c[ft_strlen(str)] == '\0')
		return (0);
	if (ft_strncmp(str, ".png", 4))
		return (error_handler_msg(4, str));
	return (error_handler_msg(3, str));
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
	// (void)game;
	char	*line;
	int		check;

	line = get_next_line(fd);

	printf("one: %s\n", line);
	while (line != NULL)
	{
		check = check_line(line, game);
		if (check == -1)
			return (free(line), 1);
		else if (check == 2)
			break;
		free(line);
		line = get_next_line(fd);
		printf("loop line : %s\n", line);
	}
	if (check != 2)
		return (error_handler(2)); //EOF 

	if (!eval_graph(game))
		return(free(line), -1);

	copy_map_to_game_struct(game, &line, fd);
	
	return 0;
}


int	read_file_content(char *argv[], t_game **game) {

	int fd;

	fd = open_file(argv[1]);
	if (fd == -1)
		return (-1);
	// printf("here\n");
	if (valid_direc_fc(fd, game))
		return (close(fd), 1);
	close(fd);
	if (!handle_map(game))
		return (-1);
	// validate_map();
	return 0;
}
