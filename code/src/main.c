/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 17:15:21 by ipavlov          ###   ########.fr       */
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
	if (valid_file_name(argv[1], ".cub") == 0)
	{
		if (parse_file_content(argv, &game))
			return (free_game(&game), 1);
	}
	else
		return (free_game(&game), error_handler_msg(3, ".cub"));
	if (background_f_c_draw(&game))
		return (1);
	mlx_key_hook(game->mlx, &key_stroks, &game);
	mlx_cursor_hook(game->mlx, cursor_cb, &game);
	mlx_resize_hook(game->mlx, rezise_window, &game);
	mlx_loop_hook(game->mlx, &start_game, &game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	if (game != NULL)
		free_game(&game);
	return (0);
}
	

// # SRC_FILES = src/error_handler/error_handler.c \
// # src/main.c \
// # src/parse_file/valid_file.c \
// # src/parse_file/eval_graph.c \
// # src/parse_file/read_process_map.c \
// # src/parse_file/parse_file_content.c \
// # src/parse_file/read_file_direction_f_c.c \
// # src/free/ft_free.c \
// # src/hooks/key_hook.c \
// # src/hooks/resize_hook.c \
// # src/utils/extract_info_from_file.c \
// # src/utils/check_map_line.c \
// # src/init/init_game.c \
// # src/math/game_math.c \
// # src/game_loop/start_game.c \
// # src/graph/graph.c \
// # src/graph/graph_background.c \
// # src/mini_map/mini_map.c \
// # lib/get_next_line/get_next_line.c \
// # lib/get_next_line/get_next_line_utils.c \
