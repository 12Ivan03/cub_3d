/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:33:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/14 11:01:48 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int valid_file(char *argv[]) {
	
	char *c;
	
	c = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (c && c[4] == '\0') {
		return (0);
	}
	return (error_handler(2));
}

int	valid_file_content(char *argv[]) {

	(void)argv;
	// open_file();
	// valid_direc_fc();
	// copy_map()
	// validate_map();

	return 0;
}
