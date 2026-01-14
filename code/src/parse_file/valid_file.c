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

int	valid_file_name(char *argv, char *str)
{
	char	*c;
	char	*s;

	s = ft_strrchr(argv, '/');
	if (s == NULL)
	{
		if (ft_strlen(argv) < 5)
			return (1);
	}
	else if (ft_strlen(s) <= 5)
		return (1);
	c = ft_strnstr(argv, str, ft_strlen(argv));
	if (c && c[ft_strlen(str)] == '\0')
		return (0);
	return (1);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-error_handler_msg(1, file));
	return (fd);
}
