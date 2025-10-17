/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:42 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/17 17:17:12 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_game *init_game(void)
{	
	t_game *game;
	game = malloc(sizeof(*game));
	if(!game)
		return NULL;
	ft_memset(game, 0, sizeof(*game));
	
	game->mlx = NULL;
	game->height = HEIGHT_WALL;
	game->width = WIDTH_WALL;
	game->fov = FOV;
	game->height_window = HEIGHT_WINDOWS;
	game->width_window = WIDTH_WINDOWS;
	game->graph = malloc(sizeof(*game->graph));
	if (!game->graph)
		return (free(game), NULL);
	ft_memset(game->graph, 0, sizeof(*game->graph));
	
	for (int i = 0; i < 4; i++)
		game->graph->walls[i] = NULL;

	game->graph->C = (t_rgb){ .rgb = {-1, -1, -1}};
	game->graph->F = (t_rgb){ .rgb = {-1, -1, -1}};
	
	return (game);
}