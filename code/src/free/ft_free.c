/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:58:54 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/17 15:53:00 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void ft_free_any(void **free_val)
{
	if (free_val == NULL)
		return ;
	free(free_val);
	free_val = NULL;
}

void	free_game_graph(t_game **game)
{
	ft_free_any((void *)(*game)->graph);
}

void	free_game(t_game **game)
{
	if ((*game)->graph != NULL)
		free_game_graph(game);
	free(*game);
	*game = NULL;
}

/* t_game *init_game(void)
{	
	t_game *game;
	game = malloc(sizeof(t_game));
	ft_memset(game, 0, sizeof(game));
	game->height = HEIGHT_WALL;
	game->width = WIDTH_WALL;
	game->fov = FOV;
	game->height_window = HEIGHT_WINDOWS;
	game->width_window = WIDTH_WINDOWS;
	game->graph = malloc(sizeof(t_graph));
	return (game);
} */