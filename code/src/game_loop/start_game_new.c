/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:27:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 12:12:54 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES
#include "cub3d.h"
#include <math.h>

void mm_fill_rect_fix(mlx_image_t *img, int x, int y, int w, int h, uint32_t c)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            mlx_put_pixel(img, x + xx, y + yy, c);
}

void	draw_background_mini_map(t_game **game)
{
	int i;
    int j;

    i = 0;
    while (i < (*game)->height)
    {
        j = 0;
        while (j < (*game)->width)
        {
            int px = j * 8;
            int py = i * 8;

            char cell = (*game)->map[i][j];
            if (cell == '1')
                mm_fill_rect_fix((*game)->mini_map_image, px, py, 8, 8, 0x777777FF);
            else
                mm_fill_rect_fix((*game)->mini_map_image, px, py, 8, 8, 0x101000AA);
            j++;
        }
        i++;
    }
}

void	start_game(void *param)
{
	t_game **game;
	int			ray;
	float			curr_ang;
	t_line			line;

	game = (t_game **)param;
	// printf("Player pos >> x:%f (%d), y: %f (%d), Player angle: %f\n", PLAYER.position.x, (int)(PLAYER.position.x / GRID_SIZE), PLAYER.position.y, (int)(PLAYER.position.y / GRID_SIZE), PLAYER.angle_alpha);
	// printf("Size of map >> y:%d, x: %d\n", (*game)->height, (*game)->width);
	// printf("test ft_tan for PI: %f, 2*PI: %f, PI/2:%f \n", ft_tan(180), ft_tan(360), ft_tan(90));
	// if (background_f_c_draw(game))// shoudl call it once!
	// 	return (1);
	ray = 0;
	ft_bzero((*game)->foreground->pixels, (*game)->foreground->width * (*game)->foreground->height * 4);
	ft_bzero((*game)->mini_map_image->pixels, (*game)->mini_map_image->width * (*game)->mini_map_image->height * sizeof(uint32_t));
	draw_background_mini_map(game);

	while (ray < WW)
	{
		curr_ang = ((float)ray / (float)WW) * (float)(FOV) - (float)(FOV) / 2;
		line.angle = PLAYER.angle_alpha - curr_ang;
		check_angle(&line.angle);

		// ----------------------
		// DDA raycasting (tile stepping)
		// ----------------------
		double pos_x = (double)PLAYER.position.x / (double)GRID_SIZE;
		double pos_y = (double)PLAYER.position.y / (double)GRID_SIZE;
		double ang = (double)deg_to_rad(line.angle);
		double ray_dir_x = cos(ang);
		double ray_dir_y = -sin(ang);
		int map_x = (int)pos_x;
		int map_y = (int)pos_y;
		double delta_dist_x = (ray_dir_x == 0.0) * 1e30 + (ray_dir_x != 0.0) * fabs(1.0 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0.0) * 1e30 + (ray_dir_y != 0.0) * fabs(1.0 / ray_dir_y);
		int step_x;
		int step_y;
		double side_dist_x;
		double side_dist_y;
		int side = 0;
		// directions
		step_x = (ray_dir_x >= 0.0) * 2 - 1; // left or right
		step_y = (ray_dir_y >= 0.0) * 2 - 1; // up or down
		side_dist_x = ((double)map_x + 1.0 * (step_x == 1) - pos_x) * delta_dist_x * step_x;
		side_dist_y = ((double)map_y + 1.0 * (step_y == 1) - pos_y) * delta_dist_y * step_y;
		// if (ray_dir_x < 0.0)
		// {
		// 	step_x = -1;
		// 	side_dist_x = (pos_x - (double)map_x) * delta_dist_x;
		// }
		// else
		// {
		// 	step_x = 1;
		// 	side_dist_x = ((double)map_x + 1.0 - pos_x) * delta_dist_x;
		// }
		// if (ray_dir_y < 0.0)
		// {
		// 	step_y = -1;
		// 	side_dist_y = (pos_y - (double)map_y) * delta_dist_y;
		// }
		// else
		// {
		// 	step_y = 1;
		// 	side_dist_y = ((double)map_y + 1.0 - pos_y) * delta_dist_y;
		// }

		while (map_x >= 0 && map_x < (*game)->width && map_y >= 0 && map_y < (*game)->height)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0; // vertical side
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1; // horizontal side
			}
			if (map_x < 0 || map_x >= (*game)->width || map_y < 0 || map_y >= (*game)->height)
				break;
			if ((*game)->map[map_y][map_x] == '1')
				break;
		}

		// Compute distance to wall hit (in tiles)
		double wall_dist_tiles;
		if (side == 0)
			wall_dist_tiles = side_dist_x - delta_dist_x;
		else
			wall_dist_tiles = side_dist_y - delta_dist_y;
		if (wall_dist_tiles < 0.0)
			wall_dist_tiles = 0.0;

		// Intersection point in world coordinates
		double hit_x = (pos_x + wall_dist_tiles * ray_dir_x) * (double)GRID_SIZE;
		double hit_y = (pos_y + wall_dist_tiles * ray_dir_y) * (double)GRID_SIZE;

		line.a = (t_coordinates){(float)hit_x, (float)hit_y};
		line.b = (t_coordinates){(float)hit_x, (float)hit_y};

		// Set hit type based on which side we crossed
		line.hit = (side == 0) * ((step_x < 0) * 2) + (side == 1) * (1 + (step_y >= 0) * 2);
		// if (side == 0)
		// 	line.hit = (step_x < 0) ? 2 : 0; // West : East
		// else
		// 	line.hit = (step_y < 0) ? 1 : 3; // North : South

		draw_col(game, line, ray, curr_ang);
		draw_mini_map(game);

		ray++;
	}

	// exit(0);
	// printf("break main loop \n\n\n");
	
	// mlx_loop((*game)->mlx);        // <<< THIS runs the render/event loop
    // mlx_terminate((*game)->mlx);
	// return (0);
}