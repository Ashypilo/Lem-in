/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:06:55 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 19:37:35 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	void	create_g(t_graf *g)
{
	g->space = 0;
	g->minus = 0;
	g->ants = 0;
	g->max_room = 0;
	g->matrix = 0;
	g->stop = 0;
	g->x = -1;
	g->y = -1;
	g->no_path = 0;
	g->start = -2;
	g->end = -2;
	g->coord = 0;
	g->size = 5000;
	g->size_minus = 5000;
	g->rooms = 0;
	g->connect = 0;
	g->start_link = 1;
	g->num = 0;
}

static	void	write_roads_char(int *arr, t_graf *g)
{
	int			j;

	j = 0;
	while (arr[j] != -1)
	{
		if (j == 0)
			ft_putstr(g->int_rooms[g->start]);
		else
		{
			write(1, "-", 1);
			ft_putstr(g->int_rooms[arr[j]]);
		}
		j++;
	}
	write(1, "\n", 1);
}

static	void	bonus_l(t_graf *g)
{
	write(1, "Here is the number of lines required: ", 38);
	ft_putnbr(g->number_lines);
	write(1, "\n", 1);
	write(1, "My is the number of lines: ", 27);
	ft_putnbr(g->num);
	write(1, "\n", 1);
	write(1, "Rooms: ", 7);
	ft_putnbr(g->max_room);
	write(1, "\n", 1);
}

static	void	out_bonus(t_graf *g, char **argv, t_roads *r, int argc)
{
	if (argc == 2)
	{
		g->x = 0;
		if (ft_strcmp(argv[1], "--r") == 0)
		{
			r = g->start_road;
			write(1, "Used roads:\n", 12);
			while (r)
			{
				write_roads_char(r->connect, g);
				r = r->next;
				g->x++;
			}
			write(1, "Used roads:", 11);
			ft_putnbr(g->x);
			write(1, "\n", 1);
		}
		else if (ft_strcmp(argv[1], "--l") == 0)
			bonus_l(g);
	}
}

int				main(int argc, char **argv)
{
	int			fd;
	t_graf		*g;
	t_roads		*r;

	g = (t_graf*)malloc(sizeof(t_graf) * 1);
	r = NULL;
	create_g(g);
	if (argc == 2 && (ft_strcmp(argv[1], "--l") != 0 &&
		ft_strcmp(argv[1], "--r") != 0))
	{
		write(1, "\nFlaggs:\n", 9);
		write(1, "        --l : output of completed steps.\n", 41);
		write(1, "        --r : output of used roads.\n", 37);
	}
	else if (argc <= 2)
	{
		fd = 0;
		if (ft_lem_in(g, fd) == 0)
			out_bonus(g, argv, r, argc);
		else
			write(1, "ERROR\n", 6);
	}
	return (0);
}
