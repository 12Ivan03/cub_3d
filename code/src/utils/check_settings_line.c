/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_settings_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:56:43 by ipavlov           #+#    #+#             */
/*   Updated: 2025/12/22 16:49:42 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int eval_dirs(char *trim_line) {
	const char *dirs[6]= {"EA ", "NO ", "WE ", "SO ", "F ","C "};// TODO:  add DO for doors

	for (int i = 0; i < 4; i++) {
		if (!ft_strncmp(trim_line, dirs[i], 3))
			return (i);
	}
	for (int i = 4; i < 6; i++) {
		if (!ft_strncmp(trim_line, dirs[i], 2))
			return (i);
	}
	return (-1);
}

t_rgb extract_color(char *str)
{
	t_rgb temp_color;
	char *substr;
	char *cstr;
	int pos;

	cstr = str;
	// printf("HERE -> %p\n", str);
	if (ft_strchr(cstr, ',') == ft_strrchr(cstr, ','))
		return ((t_rgb){ .rgb = {-1,-1,-1}}); // just return rgb... its already define as -1-1-1we have ap roblem!!!
	for (int i = 0; i < 3; i++)
	{
		// printf("HERE%d\n",i);
		if (ft_strchr(cstr, ',') != NULL)
		{
			pos = ft_strchr(cstr, ',') - cstr;
			// printf("strstr -> <%p>\n", ft_strchr(cstr, ','));
			// printf("pos: %d\n", pos);
			substr = ft_substr(cstr, 0, pos);
			// printf("Substr -> %s\n", substr);
			temp_color.rgb[i] = ft_atoi(substr);
			free(substr);
			if (temp_color.rgb[i] > 255 || temp_color.rgb[i] < 0)
				return ((t_rgb){ .rgb = {-1,-1,-1}});
			cstr += (pos + 1);
			// printf("TEMO_COLOR PRINTSNGFJD ______> %d\n",temp_color.rgb[i]);
		}
		else
		{
			temp_color.rgb[i] = ft_atoi(cstr);
			// free(cstr);
			if (temp_color.rgb[i] > 255)
				return ((t_rgb){ .rgb = {-1,-1,-1}});
			// printf("TEMO_COLOR PRINTSNGFJD ______> %d\n",temp_color.rgb[i]);
		}
	}
		// printf("HERE%d\n",i);
	// 	printf("leaving HERE\n");
	// printf("HERE -> %p\n", str);
	
	return (temp_color);
}

int	check_line(char *line, t_game **game)
{
	char			*trim_line;
	char			*extract;
	mlx_texture_t	*tex;
	t_rgb 			temp_col;
	int				i;
	
	trim_line = ft_strtrim(line, " ");
	if (!trim_line)
		return (error_handler_msg(2, "Malloc error"));
	if (*trim_line == '\n')
		return (free(trim_line), 0);
		
	i = eval_dirs(trim_line);
	if (i == -1)
		return (free(trim_line), 2);
	extract = ft_strtrim(trim_line + 1 + (i < 4), " \n\r");
	if (!extract)
		return (free(trim_line), error_handler_msg(2, "Malloc error"));
	free(trim_line);
	
	if (i < 4) // TODO:  || 6 )// for doors
	{
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
	}
	else if (i >= 4 && i < 6)
	{
		temp_col = extract_color(extract);
		if (i == 4)
			(*game)->graph->F = temp_col;
		if (i == 5)
			(*game)->graph->C = temp_col;
		free(extract);	
	}
	else
		free(extract);
	
	return (0);
}

// "10 NWSE" 
/*
Load PNG textures (NO/SO/WE/EA)

Pipeline: mlx_load_png → mlx_texture_to_image → delete the texture (keep the image) → mlx_image_to_window.
*/ 

