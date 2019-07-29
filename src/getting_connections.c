/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_connections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:52:37 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 15:01:46 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	int		search_int_room(char *s1, char *s2, char c)
{
	int			i;

	i = 0;
	while (s1[i] != c && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s2[i] == '\0' && s1[i] == c)
		return (0);
	return (1);
}

static	void	write_connect_in_arr(t_graf *g, int i)
{
	while (g->int_rooms[g->rooms])
	{
		if (search_int_room(g->line, g->int_rooms[g->rooms], '-') == 0)
		{
			g->x = g->rooms;
			break ;
		}
		g->rooms++;
	}
	while (g->line[i] != '-')
		i++;
	i++;
	g->rooms = 0;
	while (g->int_rooms[g->rooms])
	{
		if (search_int_room(&g->line[i], g->int_rooms[g->rooms], '\0') == 0)
		{
			if (g->rooms != g->x)
				g->y = g->rooms;
			break ;
		}
		g->rooms++;
	}
}

static	int		**malloc_matrix(int **matrix, int room)
{
	int			i;
	int			j;

	j = 0;
	i = 0;
	matrix = (int**)malloc(sizeof(int*) * room + 1);
	while (room >= i)
		matrix[i++] = (int*)malloc(sizeof(int) * room + 1);
	i = 0;
	while (i <= room)
	{
		j = 0;
		while (j <= room)
			matrix[i][j++] = 0;
		i++;
	}
	return (matrix);
}

static	void	start_link(t_graf *g)
{
	if (g->x == g->start || g->y == g->start)
		g->start_link = 0;
}

void			getting_connections(t_graf *g)
{
	int			i;

	i = 0;
	g->x = -1;
	g->y = -1;
	if (g->start == -1 || g->end == -1 || g->end == -2 || g->start == -2)
		g->stop = 1;
	g->space = 0;
	g->rooms = 0;
	if (g->matrix == NULL)
		g->matrix = malloc_matrix(g->matrix, g->max_room);
	write_connect_in_arr(g, i);
	start_link(g);
	if (g->x == -1 || g->y == -1)
		g->stop = 1;
	else
	{
		if (g->x > g->max_room || g->y > g->max_room)
			g->stop = 1;
		g->matrix[g->x][g->y] = 1;
		g->matrix[g->y][g->x] = 1;
	}
}
