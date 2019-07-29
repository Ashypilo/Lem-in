/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:20:34 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/21 17:24:48 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	void	push_ants(t_graf *g, t_roads *r, int i)
{
	if (r->mov_ant[i] != 0 && r->connect[i] != g->end)
	{
		write(1, "L-", 1);
		ft_putnbr(r->mov_ant[i]);
		write(1, "-", 1);
		ft_putstr(g->int_rooms[r->connect[i]]);
		write(1, " ", 1);
		r->mov_ant[i + 1] = r->mov_ant[i];
		r->mov_ant[i] = 0;
	}
	else if (r->connect[i] == g->end && r->mov_ant[i] != 0)
	{
		write(1, "L-", 1);
		ft_putnbr(r->mov_ant[i]);
		write(1, "-", 1);
		ft_putstr(g->int_rooms[r->connect[i]]);
		write(1, " ", 1);
		r->mov_ant[i] = 0;
	}
}

void			moving_ants(t_graf *g, t_roads *r)
{
	int i;

	r = g->start_road;
	while (r)
	{
		i = r->connect[0];
		while (i != 0)
		{
			push_ants(g, r, i);
			i--;
		}
		r = r->next;
	}
	g->num++;
	write(1, "\n", 1);
}

static	int		search_zero(t_roads *r)
{
	int i;

	while (r)
	{
		i = 1;
		while (i != (r->connect[0] + 1))
		{
			if (r->mov_ant[i] != 0)
				return (1);
			i++;
		}
		r = r->next;
	}
	return (0);
}

static	void	write_priority_roads(t_graf *g, t_roads *r)
{
	int			i;
	int			k;

	i = 0;
	while (r)
	{
		if (r->prev == NULL)
			r->turn = 0;
		else if (r->prev != NULL)
		{
			k = i - 1;
			r->turn = 0;
			while (k >= 0)
			{
				r->turn += r->connect[0] - g->depth_roads[k];
				k--;
			}
		}
		r = r->next;
		i++;
	}
}

void			start_ants(t_graf *g, t_roads *r)
{
	r = sorting_roads(g);
	create_arr_move_ant(g, r);
	write_priority_roads(g, r);
	start_ants_on_the_roads(g, r);
	while (search_zero(g->start_road) == 1)
		moving_ants(g, r);
}
