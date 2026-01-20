/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/20 13:53:33 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
		return (error_handler(1));
	game = init_game();
	if (!game)
		return (1);
	if (valid_file_name(argv[1], ".cub"))
		return (free_game(&game), error_handler_msg(3, ".cub"));
	if (parse_file_content(argv, &game))
		return (free_game(&game), 1);
	if (background_f_c_draw(&game))
		return (1);
	mlx_key_hook(game->mlx, &key_stroks, &game);
	mlx_cursor_hook(game->mlx, cursor_cb, &game);
	mlx_resize_hook(game->mlx, rezise_window, &game);
	mlx_loop_hook(game->mlx, &start_game, &game);
	mlx_loop(game->mlx);
	if (game != NULL)
		free_game(&game);
	return (0);
}
