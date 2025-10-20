/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:58:54 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/20 17:54:50 by ipavlov          ###   ########.fr       */
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

void	free_link_list(t_list *list)
{
	t_list *tmp;
	t_list *next;

	tmp = list;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = next;	
	}
	// free(list);
}

void	free_map(char **arr, int i)
{
	if (i > 0 && arr != NULL)
	{
		while (--i >= 0)
		{
			if (arr[i] != NULL)
			{
				free(arr[i]);
				arr[i] = NULL;
			}
		}
		// if ()
		free(arr);
		arr = NULL;
	}
	// (*arr) = NULL;
}

void	free_game(t_game **game)
{
	if ((*game)->graph != NULL)
		free_game_graph(game);
	if ((*game)->copy_map != NULL)
		free_link_list((*game)->copy_map);
	if ((*game)->map != NULL)
		free_map((*game)->map, (*game)->height);
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