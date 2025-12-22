/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 12:47:45 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// #define COLLIDE_PAD 0.0f  /* keep a small buffer from walls */

static int is_walkable(t_game **game, float x, float y)
{
    int tx = (int)(x / GRID_SIZE);
    int ty = (int)(y / GRID_SIZE);

    if (tx < 0 || tx > (*game)->width || ty < 0 || ty > (*game)->height )
		return 0;
	// printf("tx=> %d; ty=> %d, grid: %c\n",tx,ty, (*game)->map[ty][tx]);
    return ((*game)->map[ty][tx] != '1');
}

void	close_game(t_game **game)
{
	free_game(game);
	exit(0);
}


void	key_right(t_game **game)
{
	(*game)->player.angle_alpha -= ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
	// start_game(game);
}

void	key_left(t_game **game)
{
	(*game)->player.angle_alpha += ROTATION_AGNLE;
	check_angle(&(*game)->player.angle_alpha);
	// start_game(game);
}
// UP AND DOWN
void	key_up(t_game **game)
{
	// (*game)->player.angle_alpha -=ROTATION_AGNLE;
	// check_angle(&(*game)->player.angle_alpha);
	// start_game(game);
	float rad = deg_to_rad((*game)->player.angle_alpha);
    float nx = (*game)->player.position.x + cosf(rad) * (*game)->move_speed;
    float ny = (*game)->player.position.y - sinf(rad) * (*game)->move_speed;

    /* optional small collision padding: test several probe points */
    if (is_walkable(game, nx, ny))
	// && is_walkable(game, nx - COLLIDE_PAD, ny - COLLIDE_PAD))
    {
        (*game)->player.position.x = nx;
        (*game)->player.position.y = ny;
		// printf(">player.position.x=> %f; >player.position.y=> %f,\n >>player>angel ==> %f \n\n",(*game)->player.position.x / GRID_SIZE,(*game)->player.position.y / GRID_SIZE, (*game)->player.angle_alpha);

    }
    // start_game(game);
}

void	key_down(t_game **game)
{
	// (*game)->player.angle_alpha +=ROTATION_AGNLE;
	// check_angle(&(*game)->player.angle_alpha);
	// start_game(game);
	float rad = deg_to_rad((*game)->player.angle_alpha);
    float nx = (*game)->player.position.x - cosf(rad) * (*game)->move_speed;
    float ny = (*game)->player.position.y + sinf(rad) * (*game)->move_speed;

    if (is_walkable(game, nx, ny)) // && is_walkable(game, nx - COLLIDE_PAD, ny - COLLIDE_PAD))
    {
        (*game)->player.position.x = nx;
        (*game)->player.position.y = ny;
		// printf(">player.position.x=> %f; >player.position.y=> %f,\n >>player>angel ==> %f \n\n",(*game)->player.position.x  / GRID_SIZE,(*game)->player.position.y  / GRID_SIZE, (*game)->player.angle_alpha);

    }
    // start_game(game);
}	



void	key_stroks(mlx_key_data_t keydata, void *params)
{
	(void) params;
	(void) keydata;
	t_game **game;

	game = (t_game **)params;

	if (mlx_is_key_down((*game)->mlx, MLX_KEY_UP) || mlx_is_key_down((*game)->mlx, MLX_KEY_W))
		key_up(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_DOWN) || mlx_is_key_down((*game)->mlx, MLX_KEY_S))
		key_down(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_LEFT) || mlx_is_key_down((*game)->mlx, MLX_KEY_A))
		key_left(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_RIGHT) || mlx_is_key_down((*game)->mlx, MLX_KEY_D))
		key_right(game);
	if (mlx_is_key_down((*game)->mlx, MLX_KEY_ESCAPE))
		close_game(game);
	// if (mlx_is_key_down((*game)->mlx, MLX_KEY_SPACE)) {
		// hanlde_map(game);
	// 	(*game)->mini_map_info.tile = -(*game)->mini_map_info.tile;
	// if tile <= 0 
	// 	hide map 
	// else 
	// 	show_map
	// }
}


void cursor_cb(double xpos, double ypos, void *param)
{
	t_game **game;

	game = (t_game **)param;
	(void) ypos;
	if ((*game)->mouse_y == -1)
		(*game)->mouse_y = xpos;
	
	if (mlx_is_mouse_down((*game)->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if ((*game)->mouse_y < xpos) {
			(*game)->player.angle_alpha -= ROTATION_AGNLE;
			(*game)->mouse_y = xpos;
		} else {
			(*game)->player.angle_alpha += ROTATION_AGNLE;
			(*game)->mouse_y = xpos;
		}
		check_angle(&(*game)->player.angle_alpha);
		// printf("xpos: %f, (*game)->mouse_y : %f\n", xpos, (*game)->mouse_y);
		
	}

}
