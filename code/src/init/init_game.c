/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:42 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 17:16:08 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game *init_game(void)
{	
	int i;
	t_game *game;
	game = malloc(sizeof(*game));
	if(!game)
		return NULL;
	ft_memset(game, 0, sizeof(*game));
	
	game->mlx = NULL;
	game->copy_map = NULL;
	game->height = 0;
	game->width = 0;
	game->height_wall = HEIGHT_WALL;
	game->width_wall = WIDTH_WALL;
	game->fov = INIT_FOV;
	game->map = NULL;
	game->player.position.x = -1;
	game->player.position.y = -1;
	game->player.angle_alpha = 0;
	game->height_window = HEIGHT_WINDOWS;
	game->width_window = WIDTH_WINDOWS;
	game->move_speed = MOVE_SPEED;
	game->graph = malloc(sizeof(*game->graph));
	if (!game->graph)
		return (free(game), NULL);
	ft_memset(game->graph, 0, sizeof(*game->graph));
	game->graph->proj_dist = (WIDTH_WINDOWS / 2) / tan(deg_to_rad(game->fov / 2));
	i = 0;
	while (i < 4)
		game->graph->walls[i++] = NULL;
	game->graph->C = (t_rgb){.rgb = {-1, -1, -1}};
	game->graph->F = (t_rgb){.rgb = {-1, -1, -1}};
	game->mouse_y = -1;
	game->mini_map_info.tile = 10;
	game->mlx = mlx_init(WIDTH_WINDOWS, HEIGHT_WINDOWS, "cub3d", true);
	if (!game->mlx)
		return (free_game(&game), error_handler(7), NULL);
	game->foreground = mlx_new_image(game->mlx, WIDTH_WINDOWS, HEIGHT_WINDOWS);
	game->background = mlx_new_image(game->mlx, WIDTH_WINDOWS, HEIGHT_WINDOWS);
	game->mini_map_image = mlx_new_image(game->mlx, WIDTH_WINDOWS, HEIGHT_WINDOWS);
	if (game->foreground == NULL || game->background == NULL \
		|| game->mini_map_image  == NULL)
		return (free_game(&game), error_handler(7), NULL);
	if (mlx_image_to_window(game->mlx, game->background, 0 ,0) || \
		mlx_image_to_window(game->mlx, game->foreground, 0 ,0) || \
		mlx_image_to_window(game->mlx, game->mini_map_image, 50, 20))
		return (free_game(&game), error_handler(7), NULL);
	return (game);
}