/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_roads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:39:55 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 20:45:56 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void			create_arr_move_ant(t_graf *g, t_roads *r)
{
	int			i;
	int			j;

	j = 0;
	g->depth_roads = (int*)malloc(sizeof(int) * g->max_room);
	while (r)
	{
		g->depth_roads[j] = r->connect[0];
		r->mov_ant = (int*)malloc(sizeof(int) * (r->connect[0]) + 1);
		r->mov_ant[0] = g->start;
		r->mov_ant[r->connect[0] + 1] = -1;
		i = 1;
		while (r->mov_ant[i] != -1)
		{
			r->mov_ant[i] = 0;
			i++;
		}
		j++;
		r = r->next;
	}
	g->depth_roads[j] = -1;
}

static	t_roads	*start_road(t_roads *pr, t_roads *st, t_roads *n, t_roads *h)
{
	pr = st;
	st = st->next;
	n = st->next;
	st->prev = NULL;
	st->next = pr;
	st->next->next = n;
	h = st;
	return (h);
}

static	t_roads	*else_road(t_roads *pr, t_roads *st, t_roads *n, t_roads *h)
{
	pr = st;
	st = st->next;
	n = st->next;
	st->prev = pr->prev;
	st->prev->next = st;
	st->next = pr;
	st->next->next = n;
	st = h;
	return (st);
}

static	t_roads	*sort(t_roads *pr, t_roads *st, t_roads *n, t_roads *h)
{
	while (st)
	{
		if (st->next == NULL)
			st = st->next;
		else if (st->next->connect[0] < st->connect[0] &&
				st->prev == NULL)
		{
			h = start_road(pr, st, n, h);
			st = h;
		}
		else if (st->next->connect[0] < st->connect[0] &&
				st->prev != NULL)
			st = else_road(pr, st, n, h);
		else
		{
			pr = st;
			st = st->next;
			st->prev = pr;
			st->prev->next = st;
		}
	}
	return (h);
}

t_roads			*sorting_roads(t_graf *g)
{
	t_roads *start;
	t_roads *prev;
	t_roads *next;
	t_roads *head;

	start = g->start_road;
	start->prev = NULL;
	prev = NULL;
	next = NULL;
	head = start;
	head = sort(prev, start, next, head);
	start = head;
	g->start_road = head;
	return (head);
}
