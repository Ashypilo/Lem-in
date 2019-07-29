/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:21:33 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 18:44:47 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static int	least_one_connection(t_graf *g, int x, int y)
{
	int		i;

	i = 0;
	while (g->coord_x[x][i] != 2147483647)
	{
		if (g->coord_x[x][i] == y)
			return (1);
		i++;
	}
	g->coord_x[x][i] = y;
	g->coord_x[x][i + 1] = 2147483647;
	i = 0;
	while (g->coord_y[y][i] != 2147483647)
	{
		if (g->coord_y[y][i] == x)
			return (1);
		i++;
	}
	g->coord_y[y][i] = x;
	g->coord_y[y][i + 1] = 2147483647;
	return (0);
}

int			coord_plus(t_graf *g, int x, int y, int i)
{
	if (x >= g->size || y >= g->size)
	{
		if (x > 50000 || y > 50000)
			return (1);
		while (i >= g->size)
			malloc_matrix_coordinate(g);
	}
	if (g->coord_x[x][0] != 2147483647 && g->coord_y[y][0] != 2147483647)
	{
		if (least_one_connection(g, x, y) == 1)
			return (1);
	}
	else
	{
		if (least_one_connection(g, x, y) == 1)
			return (1);
	}
	return (0);
}
