/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_config_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:56:43 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/09 12:20:50 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	eval_dirs(char *trim_line)
{
	const char	*dirs[6] = {"EA ", "NO ", "WE ", "SO ", "F ", "C "};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(trim_line, dirs[i], 3))
			return (i);
		i++;
	}
	i = 4;
	while (i < 6)
	{
		if (!ft_strncmp(trim_line, dirs[i], 2))
			return (i);
		i++;
	}
	return (-1);
}

int	parse_and_config_line(char *line, t_game **game)
{
	char	*trim_line;
	char	*extract;
	int		i;

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
	if (i < 4)
		return (wall_texture(game, extract, i));
	else if (i >= 4 && i < 6)
		return (celling_floow_texture(game, extract, i));
	else
		free(extract);
	return (0);
}
