/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superposition_bhandary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:59:29 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 20:04:20 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	int			search_head_road(t_roads *r, int room)
{
	int		i;

	i = 0;
	while (r)
	{
		if (r->connect[1] == room)
			return (1);
		r = r->next;
	}
	return (0);
}

static	t_perent	*next_room_in_rd(t_room *rm, t_perent *rd, t_perent *prev)
{
	rm->con->link->was = 1;
	rd->next = (t_perent*)malloc(sizeof(t_perent) * 1);
	rd->next->perent = prev;
	rd = rd->next;
	rd->next = NULL;
	rd->link = rm->con->link;
	return (rd);
}

static	t_perent	*search(t_graf *g, t_room *rm, t_perent *rd, t_perent *prev)
{
	while (rm->con)
	{
		if (rm->con->link->was == 0 &&
				search_head_road(g->start_road, rm->con->link->room) == 0)
		{
			if (rm->con->link->room_busy == 1)
			{
				if (rm->con->link->room != g->start)
					g->swap_room = 1;
				rd = r_busy(g, rm, rd, prev);
			}
			else
				rd = next_room_in_rd(rm, rd, prev);
		}
		if (rd->link->room == g->end)
			break ;
		rm->con = rm->con->next;
	}
	return (rd);
}

static	t_perent	*bhandar(t_graf *g, t_room *rm, t_perent *rd, t_perent *h)
{
	t_link			*head_con;
	t_perent		*prev;

	while (rm->room != g->end)
	{
		rm->was = 1;
		prev = h;
		head_con = rm->con;
		if (rm->not_room == 0)
			rd = search(g, rm, rd, prev);
		rm->con = head_con;
		if (rd->link->room == g->end)
			break ;
		h = h->next;
		if (h)
		{
			if (h->link->room_busy == 1 && h->next)
				h = h->next;
			rm = h->link;
		}
		else
			rm = g->list_end;
	}
	return (rd);
}

int					superposition_bhandary(t_graf *g, t_room *rm)
{
	t_perent		*rd;

	rd = (t_perent*)malloc(sizeof(t_perent) * 1);
	rd->next = NULL;
	g->start_rd = rd;
	rd->link = rm;
	rd->perent = NULL;
	rd = bhandar(g, rm, rd, rd);
	if (write_new_road(g, rm, rd) == 1)
		return (1);
	return (0);
}
