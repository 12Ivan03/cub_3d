/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:24:18 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/05 12:37:10 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_game(t_game **game)
{
	free_game(game);
	exit(0);
}

void	key_stroks(mlx_key_data_t keydata, void *params)
{
	(void) params;
	(void) keydata;
	t_game **game;

	game = (t_game **)params;

	if (mlx_is_key_down((*game)->mlx, MLX_KEY_ESCAPE))
		close_game(game);
}
