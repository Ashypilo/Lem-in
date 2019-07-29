/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_roads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:05:52 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 20:10:07 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	void	write_new_roads(t_roads *r, t_graf *g)
{
	int			i;
	int			j;

	i = 0;
	while (r)
	{
		j = 0;
		while (g->dooble_roads[i][j] != -1)
		{
			r->connect[j] = g->dooble_roads[i][j];
			j++;
		}
		r->connect[j] = -1;
		i++;
		r = r->next;
	}
}

static	int		**write_dooble_roads(int **dooble, t_roads *r, t_graf *g)
{
	int			j;
	int			i;

	j = 0;
	r = g->start_road;
	while (r)
	{
		i = 0;
		dooble[j] = (int*)malloc(sizeof(int) * g->max_room);
		while (i != r->connect[0])
		{
			dooble[j][i] = r->connect[i];
			i++;
		}
		dooble[j][i] = g->end;
		i++;
		dooble[j][i] = -1;
		j++;
		r = r->next;
	}
	i = 0;
	g->stop = j;
	return (dooble);
}

static	int		search_same(t_graf *g, int i, int room)
{
	int			j;

	while (i < g->stop)
	{
		j = 1;
		while (g->dooble_roads[i][j] != g->end &&
				j != g->dooble_roads[i][0])
		{
			if (g->dooble_roads[i][j] == room)
			{
				g->swap_next = j;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static	void	swap_all(t_graf *g)
{
	int			i;
	int			j;
	int			same;

	i = 0;
	while (i < g->stop)
	{
		j = 1;
		same = 0;
		while (g->dooble_roads[i][j] != g->end && j != g->dooble_roads[i][0])
		{
			same = search_same(g, i + 1, g->dooble_roads[i][j]);
			if (same != 0 && g->dooble_roads[i][j + 1] != g->end)
			{
				g->swap_start = j;
				swap_dubl_roads(g, same, i);
			}
			j++;
		}
		i++;
	}
}

int				swap_roads(t_graf *g, t_roads *r)
{
	int			i;

	i = 0;
	while (r)
	{
		i++;
		r = r->next;
	}
	g->dooble_roads = (int**)malloc(sizeof(int*) * i + 1);
	g->dooble_roads = write_dooble_roads(g->dooble_roads, r, g);
	swap_all(g);
	i = 0;
	if (best_roads(g) == 1)
	{
		write_new_roads(g->start_road, g);
		while (i < g->stop)
			free(g->dooble_roads[i++]);
		free(g->dooble_roads);
		return (1);
	}
	while (i < g->stop)
		free(g->dooble_roads[i++]);
	free(g->dooble_roads);
	return (0);
}
