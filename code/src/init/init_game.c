/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:42 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:08:10 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init_default(t_game **game);
static bool	graph_init_default(t_game **game);
static bool	game_create_mlx(t_game **game);
static bool	game_create_attach_image(t_game **game);

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(*game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(*game));
	game_init_default(&game);
	if (!graph_init_default(&game))
		return (free_game(&game), error_handler(4), NULL);
	if (!game_create_mlx(&game))
		return (free_game(&game), error_handler(7), NULL);
	if (!game_create_attach_image(&game))
		return (free_game(&game), error_handler(7), NULL);
	return (game);
}

static void	game_init_default(t_game **game)
{
	(*game)->mlx = NULL;
	(*game)->copy_map = NULL;
	(*game)->height = 0;
	(*game)->width = 0;
	(*game)->height_wall = HEIGHT_WALL;
	(*game)->width_wall = WIDTH_WALL;
	(*game)->fov = INIT_FOV;
	(*game)->map = NULL;
	(*game)->player.position.x = -1;
	(*game)->player.position.y = -1;
	(*game)->player.angle_alpha = 0;
	(*game)->height_window = HEIGHT_WIN;
	(*game)->width_window = WIDTH_WIN;
	(*game)->move_speed = MOVE_SPEED;
	(*game)->mouse_y = -1;
	(*game)->mini_map_info.tile = 10;
}

static bool	graph_init_default(t_game **game)
{
	int	i;

	i = 0;
	(*game)->graph = malloc(sizeof(*(*game)->graph));
	if (!(*game)->graph)
		return (false);
	ft_memset((*game)->graph, 0, sizeof(*(*game)->graph));
	(*game)->graph->proj_dist = \
(WIDTH_WIN / 2) / tan(deg_to_rad((*game)->fov / 2));
	while (i < 4)
		(*game)->graph->walls[i++] = NULL;
	(*game)->graph->C = (t_rgb){.rgb = {-1, -1, -1}};
	(*game)->graph->F = (t_rgb){.rgb = {-1, -1, -1}};
	return (true);
}

static bool	game_create_mlx(t_game **game)
{
	(*game)->mlx = mlx_init(WIDTH_WIN, HEIGHT_WIN, "cub3d", true);
	if (!(*game)->mlx)
		return (false);
	return (true);
}

static bool	game_create_attach_image(t_game **game)
{
	(*game)->foreground = mlx_new_image((*game)->mlx, WIDTH_WIN, HEIGHT_WIN);
	(*game)->background = mlx_new_image((*game)->mlx, WIDTH_WIN, HEIGHT_WIN);
	(*game)->min_map_img = mlx_new_image((*game)->mlx, WIDTH_WIN, HEIGHT_WIN);
	if ((*game)->foreground == NULL || (*game)->background == NULL \
|| (*game)->min_map_img == NULL)
		return (false);
	if (mlx_image_to_window((*game)->mlx, (*game)->background, 0, 0))
		return (false);
	if (mlx_image_to_window((*game)->mlx, (*game)->foreground, 0, 0))
		return (false);
	if (mlx_image_to_window((*game)->mlx, (*game)->min_map_img, 20, 20))
		return (false);
	return (true);
}
