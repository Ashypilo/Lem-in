/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ants_on_the_roads.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:19:38 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:59:29 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	void	road_start_end(t_graf *g, int ant)
{
	t_roads		*r;

	r = g->start_road;
	while (ant <= g->ants)
	{
		write(1, "L-", 1);
		ft_putnbr(ant);
		write(1, "-", 1);
		ft_putstr(g->int_rooms[r->connect[1]]);
		write(1, " ", 1);
		ant++;
	}
	write(1, "\n", 1);
	g->num = 1;
}

void			start_ants_on_the_roads(t_graf *g, t_roads *r)
{
	int			ant;

	ant = 1;
	r = g->start_road;
	if (r->connect[1] == g->end)
		road_start_end(g, ant);
	else
	{
		while (g->ants != 0)
		{
			r = g->start_road;
			while (r)
			{
				if (g->ants > r->turn)
				{
					r->mov_ant[1] = ant;
					ant++;
					if (g->ants != 0)
						g->ants--;
				}
				r = r->next;
			}
			moving_ants(g, r);
		}
	}
}
