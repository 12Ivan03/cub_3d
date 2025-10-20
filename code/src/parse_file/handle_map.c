/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:40:35 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/20 16:40:19 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	count_width(t_game **game)
{
	int 	counter;
	int		i;
	t_list	*tmp;
	int		len;

	counter = 0;
	i = 0;
	tmp = (*game)->copy_map; 
	while (tmp != NULL)
	{
		len = ft_strlen((char *)(tmp->content));
		if (counter <= len)
			counter = len;
		tmp = tmp->next;
	}
	return (counter);
}

int	count_height(t_game **game)
{
	return (ft_lstsize((*game)->copy_map));
}

int	find_start_position(t_game **game, int i)
{
	int	j;

	j = 0;
	while (j < (*game)->width && (*game)->map[i][j] != 0)
	{
		if (ft_strchr("NWSE", (*game)->map[i][j]))
			return (j);
		j++;
	}
	return (-1);
}

void set_position(t_game **game, int x, int y)
{
	(*game)->player.position.x = x;
	(*game)->player.position.y = y;
}

int	handle_map(t_game **game)
{
	int	i;
	int j;
	t_list *iter;
	
	i = 0;
	iter = (*game)->copy_map;
	(*game)->height = count_height(game);
	(*game)->width = count_width(game);
	(*game)->map = (char **)malloc((*game)->height * sizeof(char *));
	if (!(*game)->map)
		return (-1);
	while (i < (*game)->height)
	{
		(*game)->map[i] = (char *)ft_calloc((*game)->width, 1);
		if (!(*game)->map[i])
			return (free_map((*game)->map, i), -1);
		ft_strlcat((*game)->map[i], (char *)iter->content, (*game)->width);
		j = find_start_position(game, i);
		if (j != -1)
		{
			printf("Found position: %d, %d", i, j);
			set_position(game, j, i);
		}
		iter = iter->next;
		i++;
	}
	{
		// t_list *iter = (*game)->copy_map; 
		// while (iter != NULL) {
		// 	printf("%s\n",(char *)iter->content);
		// 	iter = iter->next;
		// }	
		
		for (int i = 0; i < (*game)->height; i++) {
			printf(">%s<\n", (*game)->map[i]);
		}
		printf("height: %d\n", (*game)->height );
		printf("width: %d\n", (*game)->width );
		printf("X: %d\n", (*game)->player.position.x );
		printf("Y: %d\n", (*game)->player.position.y );
	}
	return 1;
}
