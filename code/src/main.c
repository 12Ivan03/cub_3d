/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:46:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/11/29 16:23:02 by ipavlov          ###   ########.fr       */
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
		if(read_file_content(argv, &game) || start_game(&game))
		{
			free_game(&game);
			return(1);
		}
	}
	if (game != NULL)
		free_game(&game);
	return (0);
}
