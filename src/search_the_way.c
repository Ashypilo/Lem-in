/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_the_way.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:34:06 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:54:36 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	t_perent	*con_r(t_graf *g, t_room *rm, t_perent *rd, t_perent *prev)
{
	while (rm->con)
	{
		if (rm->con->link->was == 0)
		{
			rm->con->link->was = 1;
			rd->next = (t_perent*)malloc(sizeof(t_perent) * 1);
			rd->next->perent = prev;
			rd = rd->next;
			rd->next = NULL;
			rd->link = rm->con->link;
			if (rd->link->room == g->end)
				break ;
		}
		rm->con = rm->con->next;
	}
	return (rd);
}

static	t_perent	*short_road(t_graf *g, t_room *rm, t_perent *rd)
{
	t_link			*head_con;
	t_perent		*head_rd;
	t_perent		*prev;

	head_rd = rd;
	while (rm && rm->room != g->end)
	{
		rm->was = 1;
		prev = head_rd;
		head_con = rm->con;
		rd = con_r(g, rm, rd, prev);
		if (rd->link->room == g->end)
		{
			rm->con = head_con;
			break ;
		}
		rm->con = head_con;
		head_rd = head_rd->next;
		if (head_rd)
			rm = head_rd->link;
		else
			break ;
	}
	return (rd);
}

static	void		write_short_road(t_graf *g, t_roads *r, t_perent *rd)
{
	t_perent		*end_rd;

	r->connect[g->size + 1] = -1;
	r->connect[0] = g->size;
	end_rd = rd;
	while (rd->link->room != g->start)
	{
		if (r->connect[1] == rd->link->room)
			rd->link->not_room = 1;
		r->connect[g->size] = rd->link->room;
		g->size--;
		rd = rd->perent;
	}
}

static	void		found_short_road(t_perent *rd, t_graf *g, t_room *rm)
{
	t_perent		*end;

	end = rd;
	while (rd->link->room != g->start)
	{
		g->size++;
		rd = rd->perent;
		if (rd->link->room != g->start)
			rd->link->room_busy = 1;
	}
	g->swap_room = 0;
	write_short_road(g, g->start_road, end);
	rm = g->list_head;
	while (rm)
	{
		rm->was = 0;
		rm = rm->next;
	}
	search_roads_bhandary(g);
}

void				search_the_way(t_graf *g, t_room *rm)
{
	t_perent		*rd;
	t_perent		*start;

	g->size = 0;
	rd = (t_perent*)malloc(sizeof(t_perent) * 1);
	rd->next = NULL;
	start = rd;
	rd->link = rm;
	rd->perent = NULL;
	rd = short_road(g, rm, rd);
	if (rd->link->room == g->end)
		found_short_road(rd, g, rm);
	else
		g->no_path = 1;
	rd = start;
	while (rd)
	{
		free(rd);
		rd = rd->next;
	}
}
