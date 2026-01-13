/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:58:54 by ipavlov           #+#    #+#             */
/*   Updated: 2026/01/13 14:00:08 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_game_graph(t_game **game);
void	ft_free_any(void **free_val);
void	free_link_list(t_list *list);
void	free_map(char ***arr, int i);

void	free_game(t_game **game)
{
	if ((*game)->graph != NULL)
		free_game_graph(game);
	if ((*game)->copy_map != NULL)
		free_link_list((*game)->copy_map);
	if ((*game)->map != NULL)
		free_map(&(*game)->map, (*game)->height);
	if ((*game)->mlx != NULL)
		mlx_terminate((*game)->mlx);
	free(*game);
	*game = NULL;
}

void	ft_free_any(void **free_val)
{
	if (free_val == NULL)
		return ;
	free(free_val);
	free_val = NULL;
}

void	free_game_graph(t_game **game)
{
	ft_free_any((void *)(*game)->graph);
}

void	free_link_list(t_list *list)
{
	t_list	*tmp;
	t_list	*next;

	tmp = list;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = next;
	}
}

void	free_map(char ***arr, int i)
{
	if (*arr)
	{
		while (--i >= 0)
		{
			if ((*arr)[i] != NULL)
			{
				free((*arr)[i]);
				(*arr)[i] = NULL;
			}
		}
		free(*arr);
		*arr = NULL;
	}
}
