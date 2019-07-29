/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_busy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:21:18 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:14:19 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	int		back_room_road(t_roads *r, int room)
{
	int			i;

	while (r)
	{
		i = 1;
		while (r->connect[i] != -1)
		{
			if (r->connect[i] == room && i != 1)
			{
				return (r->connect[i - 1]);
			}
			i++;
		}
		r = r->next;
	}
	return (0);
}

static	t_room	*next_room(t_room *copy, int prev_room)
{
	t_link		*head;
	t_room		*out;

	head = copy->con;
	out = NULL;
	while (copy->con)
	{
		if (copy->con->link->room == prev_room)
			out = copy->con->link;
		copy->con = copy->con->next;
	}
	copy->con = head;
	if (out != NULL)
		return (out);
	return (copy);
}

static	int		search_busy(t_link *con, int room)
{
	t_link		*start;

	start = con;
	while (con)
	{
		if (con->link->room_busy == 0 &&
				con->link->was == 0 && con->link->room != room)
		{
			con = start;
			return (1);
		}
		con = con->next;
	}
	con = start;
	return (0);
}

t_perent		*r_busy(t_graf *g, t_room *rm, t_perent *rd, t_perent *pr)
{
	int			i;

	i = 0;
	if (search_busy(rm->con, rm->con->link->room) == 0)
	{
		i = back_room_road(g->start_road, rm->con->link->room);
		if (i != g->start)
		{
			rm->con->link->was = 1;
			rd->next = (t_perent*)malloc(sizeof(t_perent) * 1);
			rd->next->perent = pr;
			rd = rd->next;
			rd->next = NULL;
			rd->link = rm->con->link;
			rd->next = (t_perent*)malloc(sizeof(t_perent) * 1);
			rd->next->perent = rd;
			rd = rd->next;
			rd->next = NULL;
			rd->link = next_room(rm->con->link, i);
			rd->link->was = 1;
		}
	}
	return (rd);
}
