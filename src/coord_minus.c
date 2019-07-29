/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_minus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:51:09 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 18:45:58 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static int		search_dooble_coord(int **arr, int xy, int yx)
{
	int			i;

	i = 0;
	while (arr[xy][i] != 2147483647)
	{
		if (arr[xy][i] == yx)
			return (1);
		i++;
	}
	arr[xy][i] = yx;
	arr[xy][i + 1] = 2147483647;
	return (0);
}

static int		coord_x_m(t_graf *g, int x, int y)
{
	if (x < 0)
	{
		x = x * -1;
		while (x >= g->size_minus)
		{
			if (x > 50000)
				return (1);
			g->coord_x_m = more_coordinate(g->coord_x_m, g->size_minus);
			g->coord_y_m = more_coordinate(g->coord_y_m, g->size_minus);
			g->size_minus *= 2;
		}
		if (search_dooble_coord(g->coord_x_m, x, y) == 1)
			return (1);
		x = x * -1;
	}
	else
	{
		if (search_dooble_coord(g->coord_x_m, x, y) == 1)
			return (1);
	}
	return (0);
}

static int		coord_y_m(t_graf *g, int x, int y)
{
	if (y < 0)
	{
		y = y * -1;
		while (y >= g->size_minus)
		{
			if (y > 50000)
				return (1);
			g->coord_y_m = more_coordinate(g->coord_y_m, g->size_minus);
			g->coord_x_m = more_coordinate(g->coord_x_m, g->size_minus);
			g->size_minus *= 2;
		}
		if (search_dooble_coord(g->coord_y_m, y, x) == 1)
			return (1);
		y = y * -1;
	}
	else
	{
		if (search_dooble_coord(g->coord_y_m, y, x) == 1)
			return (1);
	}
	return (0);
}

int				coord_minus(t_graf *g, int x, int y)
{
	int			i;

	if (g->coord_x_m == NULL && g->coord_y_m == NULL)
	{
		g->coord_x_m = (int**)malloc(sizeof(int*) * g->size);
		g->coord_y_m = (int**)malloc(sizeof(int*) * g->size);
		i = 0;
		while (i < g->size)
		{
			g->coord_x_m[i] = (int*)malloc(sizeof(int) * g->size);
			g->coord_y_m[i] = (int*)malloc(sizeof(int) * g->size);
			g->coord_x_m[i][0] = 2147483647;
			g->coord_y_m[i][0] = 2147483647;
			i++;
		}
		g->size_minus = g->size;
	}
	if (coord_x_m(g, x, y) == 1)
		return (1);
	if (coord_y_m(g, x, y) == 1)
		return (1);
	return (0);
}
