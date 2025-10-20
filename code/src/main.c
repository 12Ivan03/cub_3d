/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/20 14:33:55 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_game *game;
	
	if (argc != 2)
		return (error_handler(1));
	game = init_game();
	game->mlx = mlx_init(game->width_window, game->height_window, "cun3d", false);
	// printf("1\n");
	if (!valid_file_name(argv, ".cub"))
	{
		if(read_file_content(argv, &game))
		{
			free_game(&game);
			return(1); //free_game(game), 
		}
		// fill the array
	}
	if (game != NULL)
		free_game(&game);
	// free the array
	return (0);
}
