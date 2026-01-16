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

int	read_validate_direc_fc(int fd, t_game **game)
{
	char	*line;
	int		check;

	check = -1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		check = parse_and_config_line(line, game);
		if (check == 1)
			return (close_gnl_fd(fd, &line), 1);
		else if (check == 2 || check == 3)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (check != 2 && check != 3)
		return (error_handler(2));
	if (check == 2)
		return (close_gnl_fd(fd, &line), error_handler(8));
	if (eval_graph(game))
		return (close_gnl_fd(fd, &line), 1);
	if (copy_map_to_game_struct(game, &line, fd))
		return (close_gnl_fd(fd, &line), 1);
	return (0);
}
