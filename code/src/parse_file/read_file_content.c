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

#include "cub3d.h"

int	read_file_content(char *argv[], t_game **game) {

	int fd;

	fd = open_file(argv[1]);
	if (fd == -1)
		return (1);
	if (valid_direc_fc(fd, game))
		return (close(fd), 1);
	close(fd);
	if (read_process_map(game)) 
		return (1);
	if (validate_struct(game))
		return (1);
	if (validate_map(game))
		return (error_handler(5));
	return (0);
}