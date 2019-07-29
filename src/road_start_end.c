/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road_start_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:12:57 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:11:24 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void		road_start_end(t_graf *g, int ant)
{
	t_roads	*r;

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
	g->ants = 0;
}
