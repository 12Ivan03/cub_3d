/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:25:03 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/24 14:05:44 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int error_handler(int er) {
	
	printf("Error\n");
	if (er == 1) {
		printf("Invalid arguments. Expected 2 arguments.\n");
	} else if (er == 2)
		printf("EOF: missing map\n");
	else if (er == 3)
		printf("er == 3\n");
	else if (er == 4)
		printf("Malloc error\n");
	else if (er == 5)
		printf("Open map\n");
	else if (er == 6)
		printf("An error occurred in the MXL42 library\n");

	return 1;
}

int error_handler_msg(int er, char *msg) {
	
	printf("Error\n");
	if (er == 1)
		printf("Could not open file: %s No such file or directory\n", msg);
	if (er == 2)
		printf("%s\n", msg);
	if (er == 3)
		printf("Invalid file extension. Expected a %s file.\n", msg);
	if (er == 4)
		printf("Invalid texture file extension. Expected a %s file.\n", msg);
	if (er == 5)
		printf("Invalid file information. Expected %s.\n", msg);
	

	return 1;
}