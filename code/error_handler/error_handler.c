/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:25:03 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/14 12:06:28 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int error_handler(int er) {
	
	printf("Error\n");
	if (er == 1) {
		printf("Invalid arguments. Expected 2 arguments.\n");
	} else if (er == 2)
		printf("Invalid file extension. Expected a .cub file.\n");

	return 1;
}