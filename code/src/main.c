/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/19 12:01:13 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_game *game;
	
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc != 2)
		return (error_handler(1));
	game = init_game();
	if (!game->mlx)
		return (error_handler(6));
	if (!valid_file_name(argv[1], ".cub"))
		if(read_file_content(argv, &game)) // || start_game(&game))
			return(free_game(&game), 1);
	if (background_f_c_draw(&game))// shoudl call it once!
		return (1);
	mlx_key_hook(game->mlx, &key_stroks, &game);
	mlx_cursor_hook(game->mlx, cursor_cb, &game);
	mlx_resize_hook(game->mlx, rezise_window , &game);
	mlx_loop_hook(game->mlx, &start_game, &game);
	mlx_loop(game->mlx);        // <<< THIS runs the render/event loop
    mlx_terminate(game->mlx);
	if (game != NULL)
		free_game(&game);
	return (0);
}
