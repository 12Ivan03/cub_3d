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


int	valid_direc_fc(int fd, t_game **game)
{
	char	*line;
	int		check;

	line = get_next_line(fd);
	while (line != NULL)
	{
		check = parse_and_config_line(line, game);
		if (check == 1)
			return (free(line), 1);
		else if (check == 2)
			break;
		free(line);
		line = get_next_line(fd);
	}
	if (check != 2)
		return (error_handler(2));
	if (eval_graph(game))
		return(free(line), 1);
	copy_map_to_game_struct(game, &line, fd);
	return 0;
}