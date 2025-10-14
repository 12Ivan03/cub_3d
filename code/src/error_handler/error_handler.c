/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:25:03 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/14 15:43:22 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int error_handler(int er) {
	
	printf("Error\n");
	if (er == 1) {
		printf("Invalid arguments. Expected 2 arguments.\n");
	} else if (er == 2)
		printf("Invalid file extension. Expected a .cub file.\n");
	else if (er == 3)
		printf("er == 3\n");

	return -1;
}

int error_handler_msg(int er, char *msg) {
	
	printf("Error\n");
	if (er == 1)
		printf("Could not open file: %s No such file or directory\n", msg);

	return -1;
}