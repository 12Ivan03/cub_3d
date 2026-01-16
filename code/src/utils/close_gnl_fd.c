/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_gnl_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:58:05 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/16 12:58:55 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_gnl_fd(int fd, char **line)
{
	while ((*line) != NULL)
	{
		free(*line);
		*line = get_next_line(fd);
	}
}
