/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_room_in_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:30:46 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 18:36:45 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	char	*ft_strdup_space(char *src, int c)
{
	int			i;
	int			j;
	char		*crs;

	i = 0;
	j = 0;
	while (src[i] != c)
		i++;
	crs = (char*)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		crs[j] = src[j];
		j++;
	}
	crs[j] = '\0';
	return (crs);
}

static	int		write_coordinate(t_graf *g, int i)
{
	int			x;
	int			y;

	x = ft_atoi(&g->line[i]);
	while (g->line[i] != ' ')
		i++;
	i++;
	y = ft_atoi(&g->line[i]);
	i = y;
	if (i < x)
		i = x;
	if (x >= 0 && y >= 0)
	{
		if (coord_plus(g, x, y, i) == 1)
			return (1);
	}
	else
	{
		if (coord_minus(g, x, y) == 1)
			return (1);
	}
	return (0);
}

static	int		search_double_room(t_graf *g)
{
	int			i;
	int			j;

	i = 0;
	while (g->int_rooms[i])
	{
		j = 0;
		if (g->int_rooms[i][j] == g->int_rooms[g->rooms][j] && g->rooms != i)
		{
			while (g->int_rooms[i][j] == g->int_rooms[g->rooms][j]
					&& g->int_rooms[i][j] != '\0' &&
					g->int_rooms[g->rooms][j] != '\0')
				j++;
			if (g->int_rooms[i][j] == '\0' &&
					g->int_rooms[g->rooms][j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static	void	write_room_in_arr(t_graf *g)
{
	if (g->start == -1)
	{
		g->int_rooms[g->rooms] = ft_strdup_space(g->line, ' ');
		g->start = g->rooms;
		if (search_double_room(g) == 1)
			g->stop = 1;
	}
	else if (g->end == -1)
	{
		g->int_rooms[g->rooms] = ft_strdup_space(g->line, ' ');
		g->end = g->rooms;
		if (search_double_room(g) == 1)
			g->stop = 1;
	}
	else
	{
		g->int_rooms[g->rooms] = ft_strdup_space(g->line, ' ');
		if (search_double_room(g) == 1)
			g->stop = 1;
	}
}

void			search_room_in_line(t_graf *g)
{
	int			i;

	malloc_arrays(g);
	write_room_in_arr(g);
	i = 0;
	while (g->line[i] != ' ')
		i++;
	i++;
	if (write_coordinate(g, i) == 1)
		g->stop = 1;
	if (g->start == -1 || g->end == -1)
		g->stop = 1;
	if (g->stop != 1)
		g->rooms++;
	if (g->max_room < g->rooms)
		g->max_room = g->rooms;
	g->minus = -1;
}
