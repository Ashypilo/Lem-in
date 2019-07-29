/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:56:15 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:09:31 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static char	**more_char_rooms(char **matrix, int size, int stop)
{
	char	**big_size;
	int		prev_size;
	int		i;

	i = 0;
	prev_size = size;
	size *= 2;
	big_size = (char**)malloc(sizeof(char*) * size + 1);
	while (i <= stop)
	{
		if (matrix[i])
			big_size[i] = ft_strdup(matrix[i]);
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (big_size);
}

static	int	**write_new_arr(int **old, int **coord, int size, int prev_size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		coord[i] = (int*)malloc(sizeof(int*) * size);
		if (i < prev_size)
		{
			while (old[i][j] != 2147483647)
			{
				coord[i][j] = old[i][j];
				j++;
			}
			coord[i][j] = 2147483647;
			free(old[i]);
		}
		else
			coord[i][0] = 2147483647;
		i++;
	}
	free(old);
	return (coord);
}

int			**more_coordinate(int **arr_old, int size)
{
	int		**arr_coord;
	int		prev_size;

	prev_size = size;
	size *= 2;
	arr_coord = (int**)malloc(sizeof(int*) * size);
	arr_coord = write_new_arr(arr_old, arr_coord, size, prev_size);
	return (arr_coord);
}

void		malloc_matrix_coordinate(t_graf *g)
{
	g->int_rooms = more_char_rooms(g->int_rooms, g->size, g->rooms);
	g->coord_x = more_coordinate(g->coord_x, g->size);
	g->coord_y = more_coordinate(g->coord_y, g->size);
	g->size *= 2;
}

void		malloc_arrays(t_graf *g)
{
	int		i;

	if (g->rooms == 0)
	{
		g->int_rooms = (char**)malloc(sizeof(char*) * g->size);
		g->coord_x = (int**)malloc(sizeof(int*) * g->size);
		g->coord_y = (int**)malloc(sizeof(int*) * g->size);
		i = 0;
		while (i < g->size)
		{
			g->coord_x[i] = (int*)malloc(sizeof(int) * g->size);
			g->coord_y[i] = (int*)malloc(sizeof(int) * g->size);
			g->coord_x[i][0] = 2147483647;
			g->coord_y[i][0] = 2147483647;
			i++;
		}
	}
	if (g->rooms >= g->size)
		malloc_matrix_coordinate(g);
}
