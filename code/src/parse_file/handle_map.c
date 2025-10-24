/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:40:35 by ipavlov           #+#    #+#             */
/*   Updated: 2025/10/24 14:29:32 by ipavlov          ###   ########.fr       */
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

int	eval_map_line(char *arr)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(arr);
	while (j < len && arr[j] != 0)
	{
		if (!ft_strchr("NWSE10 ", arr[j]))
			return (1);
		j++;
	}
	return (0);
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
	(*game)->map = (char **)malloc((*game)->height* sizeof(char *));
	if (!(*game)->map)
		return (-1);
	while (i < (*game)->height)
	{
		// printf("1\n");
		(*game)->map[i] = (char *)ft_calloc(((*game)->width + 1), 1);
		if (!(*game)->map[i])
			return (free_map(&(*game)->map, i), error_handler(4));
		ft_strlcat((*game)->map[i], (char *)iter->content, (*game)->width + 1);
		j = find_start_position(game, i);
		if (j != -1)
		{
			// printf("3\n");
			if ((*game)->player.position.x != -1 || (*game)->player.position.y != -1)
				return (free_map(&(*game)->map, i + 1), 1);
			set_position(game, j, i);
			(*game)->map[i][j] = '0';
		}
		if (eval_map_line((*game)->map[i]))
			return (free_map(&(*game)->map, i + 1), 1);
		// printf("%s\n", (*game)->map[i]);
		iter = iter->next;
		i++;
	}
	// for (int i = 0; i < (*game)->height; i++) {
	// 	printf(">%s<\n", (*game)->map[i]);
	// }
	return 0;
}

// {
// 	// t_list *iter = (*game)->copy_map; 
// 	// while (iter != NULL) {
// 	// 	printf("%s\n",(char *)iter->content);
// 	// 	iter = iter->next;
// 	// }	
	
// 	for (int i = 0; i < (*game)->height; i++) {
// 		printf(">%s<\n", (*game)->map[i]);
// 	}
// 	printf("height: %d\n", (*game)->height );
// 	printf("width: %d\n", (*game)->width );
// 	printf("X: %d\n", (*game)->player.position.x );
// 	printf("Y: %d\n", (*game)->player.position.y );
// }