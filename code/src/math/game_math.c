/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:50:17 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/05 15:25:58 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	projection_distance(t_game **game)
{
	float res;
	
	res = ((*game)->width_window / 2) / tan((*game)->fov / 2);
	return (res);
}

float distance(t_coordinates a, t_coordinates b)
{
	return (sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

void check_angle(float *angle)
{
	if (*angle < 0.0f)
		*angle +=360.0f;
	else if (*angle > 360.0f)
		*angle -=360.0f;
}
