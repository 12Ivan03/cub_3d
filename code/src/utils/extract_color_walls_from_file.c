/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_info_from_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:56:43 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 16:49:42 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_comas(char *str)
{
	int	count;

	count = 0;
	while (str && ft_strchr(str, ','))
	{
		count++;
		str = ft_strchr(str, ',') + 1;
	}
	if (count < 3)
		return (1);
	return (0);
}

t_rgb	extract_color(char *str)
{
	t_rgb	tmp_clr;
	int		i;

	i = 0;
	if (!ft_comas(str) || ft_strchr(str, ',') == ft_strrchr(str, ','))
		return ((t_rgb){ .rgb = {-1,-1,-1}});
	while (i < 3)
	{
		tmp_clr.rgb[i] = ft_atoi(str);
		if (!ft_isdigit(str[0]) || tmp_clr.rgb[i] < 0 || tmp_clr.rgb[i] > 255)
			return ((t_rgb){ .rgb = {-1,-1,-1}});
		str = ft_strchr(str, ',');
		if (i < 2 && !str)
			return ((t_rgb){ .rgb = {-1,-1,-1}});
		if (str)
			str++;
		i++;
	}
	return (tmp_clr);
}

int	wall_texture(t_game **game, char *extract, int i)
{
	mlx_texture_t	*tex;

	if (valid_file_name(extract, ".png") != 0)
		return (free(extract), error_handler_msg(3, ".png"));
	if (access(extract, R_OK) == -1)
		return (free(extract), error_handler_msg(2, strerror(errno)));
	tex = mlx_load_png(extract);
	free(extract);		
	if (!tex)
		return (error_handler_msg(2, "Failed to load png"));
	if ((*game)->graph->walls[i] == NULL)
	{
		(*game)->graph->walls[i] = mlx_texture_to_image((*game)->mlx, tex);
		mlx_delete_texture(tex);
		if (!(*game)->graph->walls[i])
			return (error_handler_msg(2, "Failed attach image to texture"));
	}
	else
		return (error_handler_msg(2, "Incorrect map file"));
	return (0);
}

int	celling_floow_texture(t_game **game, char *extract, int i)
{
	t_rgb	temp_col;

	temp_col = extract_color(extract);
	if (i == 4)
		(*game)->graph->F = temp_col;
	if (i == 5)
		(*game)->graph->C = temp_col;
	free(extract);	
	return (0);
}

// t_rgb	extract_color(char *str)
// {
// 	t_rgb	temp_color;
// 	char	*substr;
// 	char	*cstr;
// 	int		pos;
// 	int		i;
// 	i = 0;
// 	cstr = str;
// 	if (ft_strchr(cstr, ',') == ft_strrchr(cstr, ','))
// 		return ((t_rgb){ .rgb = {-1,-1,-1}});
// 	while (i < 3)
// 	{
// 		if (ft_strchr(cstr, ',') != NULL)
// 		{
// 			pos = ft_strchr(cstr, ',') - cstr;
// 			substr = ft_substr(cstr, 0, pos);
// 			temp_color.rgb[i] = ft_atoi(substr);
// 			free(substr);
// 			if (temp_color.rgb[i] > 255 || temp_color.rgb[i] < 0)
// 				return ((t_rgb){ .rgb = {-1,-1,-1}});
// 			cstr += (pos + 1);
// 		}
// 		else
// 		{
// 			temp_color.rgb[i] = ft_atoi(cstr);
// 			if (temp_color.rgb[i] > 255)
// 				return ((t_rgb){ .rgb = {-1,-1,-1}});
// 		}
// 		i++;
// 	}
// 	return (temp_color);
// }