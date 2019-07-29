/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_new_road.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:02:45 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 20:12:58 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	void	free_bad_road(t_roads *r, t_perent *rd, t_graf *g)
{
	while (rd->link->room != g->start)
	{
		if (r->connect[1] == rd->link->room)
			rd->link->not_room = 1;
		rd->link->room_busy = 0;
		rd = rd->perent;
	}
	r = g->start_road;
	while (r->next->next)
		r = r->next;
	free(r->next->connect);
	free(r->next);
	r->next = NULL;
}

static	void	write_road(t_graf *g, t_roads *r, t_perent *rd)
{
	t_perent	*end_rd;
	t_perent	*rm_head;

	r->next = (t_roads*)malloc(sizeof(t_roads) * 1);
	r->next->connect = (int*)malloc(sizeof(int) * g->max_room);
	r = r->next;
	r->next = NULL;
	r->connect[g->size + 1] = -1;
	r->connect[0] = g->size;
	end_rd = rd;
	while (rd->link->room != g->start)
	{
		r->connect[g->size--] = rd->link->room;
		rm_head = rd;
		rd = rd->perent;
	}
	if (g->swap_room == 1 && rm_head->link->not_room == 0)
	{
		if (swap_roads(g, g->start_road) == 0)
			free_bad_road(r, end_rd, g);
	}
	else if (rm_head->link->not_room == 1)
		free_bad_road(r, end_rd, g);
}

static	void	write_new_road_exist(t_graf *g, t_room *rm, t_perent *rd)
{
	t_perent	*end;
	t_roads		*r;

	g->size = 0;
	end = rd;
	while (rd->link->room != g->start)
	{
		g->size++;
		rd = rd->perent;
		if (rd->link->room_busy == 1)
			g->swap_room = 1;
		if (rd->link->room != g->start)
			rd->link->room_busy = 1;
	}
	rm = g->list_head;
	while (rm)
	{
		rm->was = 0;
		rm = rm->next;
	}
	r = g->start_road;
	while (r->next)
		r = r->next;
	write_road(g, r, end);
}

int				write_new_road(t_graf *g, t_room *rm, t_perent *rd)
{
	if (rd->link->room == g->end)
	{
		write_new_road_exist(g, rm, rd);
		rd = g->start_rd;
		while (rd)
		{
			free(rd);
			rd = rd->next;
		}
		return (1);
	}
	rd = g->start_rd;
	while (rd)
	{
		free(rd);
		rd = rd->next;
	}
	rm = g->list_head;
	while (rm)
	{
		rm->was = 0;
		rm = rm->next;
	}
	return (0);
}
