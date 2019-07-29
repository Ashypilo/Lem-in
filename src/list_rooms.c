/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:56:28 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:00:18 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static t_room	*s_con_room(t_room *dubl_rm, t_room *rm, t_room *end, int i)
{
	static		t_link *dubl_con = NULL;

	if (dubl_rm->room == i)
	{
		if (rm->con == 0)
		{
			rm->con = (t_link*)malloc(sizeof(t_link) * 1);
			dubl_con = rm->con;
		}
		else
		{
			dubl_con->next = (t_link*)malloc(sizeof(t_link) * 1);
			dubl_con = dubl_con->next;
		}
		dubl_con->link = dubl_rm;
		dubl_con->depth = 0;
		dubl_con->next = NULL;
		dubl_rm = end;
	}
	else
		dubl_rm = dubl_rm->next;
	return (dubl_rm);
}

static	void	list_coonect_room(t_room *rm, t_room *end, t_graf *g)
{
	int			i;
	int			j;
	t_room		*dubl_rm;
	t_room		*start;

	i = 0;
	start = rm;
	while (i < g->max_room)
	{
		j = 0;
		rm->con = 0;
		while (j < g->max_room)
		{
			if (g->matrix[i][j] == 1)
			{
				dubl_rm = start;
				while (dubl_rm)
					dubl_rm = s_con_room(dubl_rm, rm, end, j);
			}
			j++;
		}
		i++;
		rm = rm->next;
	}
}

static	void	else_connect(t_room *rm, t_graf *g)
{
	int			i;

	i = 1;
	while (i < g->max_room)
	{
		rm->next = (t_room*)malloc(sizeof(t_room) * 1);
		rm->next->room = -1;
		rm->next->depth = 0;
		rm->next->start = g->start;
		rm->next->end = g->end;
		rm->next->was = 0;
		rm->next->room_busy = 0;
		rm->next->not_room = 0;
		rm = rm->next;
		rm->next = NULL;
		i++;
	}
}

static	void	connect_rooms(t_room *rm, t_graf *g)
{
	int			i;
	t_room		*end;

	g->list_head = rm;
	else_connect(rm, g);
	rm = g->list_head;
	i = 0;
	while (i < g->max_room)
	{
		rm->room = i;
		if (rm->room == g->end)
			g->list_end = rm;
		i++;
		rm = rm->next;
	}
	end = rm;
	rm = g->list_head;
	list_coonect_room(rm, end, g);
	while (rm)
	{
		if (rm->room == g->start)
			g->list_start = rm;
		rm = rm->next;
	}
}

void			list_rooms(t_graf *g)
{
	t_room		*rm;
	t_roads		*r;

	rm = (t_room*)malloc(sizeof(t_room) * 1);
	rm->next = NULL;
	rm->room = -1;
	rm->depth = 0;
	rm->start = g->start;
	rm->was = 0;
	rm->not_room = 0;
	rm->room_busy = 0;
	g->head_rm = rm;
	r = (t_roads*)malloc(sizeof(t_roads) * 1);
	r->next = NULL;
	r->connect = (int*)malloc(sizeof(int) * g->max_room);
	r->connect[1] = -1;
	g->start_road = r;
	connect_rooms(rm, g);
	search_the_way(g, g->list_start);
}
