/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/05 12:28:36 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_game *game;
	
	if (argc != 2)
		return (error_handler(1));
	game = init_game();
	game->mlx = mlx_init(WIDTH_WINDOWS, HEIGHT_WINDOWS, "cub3d", true);
	if (!game->mlx)
		return (error_handler(6));
	// printf("1\n");
	if (!valid_file_name(argv[1], ".cub"))
	{
		if(read_file_content(argv, &game)) // || start_game(&game))
		{
			free_game(&game);
			return(1);
		}
	}
	if (background_f_c_draw(&game))// shoudl call it once!
		return (1);
	mlx_loop_hook(game->mlx, &start_game, &game);
	mlx_key_hook(game->mlx, &key_stroks, &game);
	mlx_loop(game->mlx);        // <<< THIS runs the render/event loop
    mlx_terminate(game->mlx);
	if (game != NULL)
		free_game(&game);
	return (0);
}
