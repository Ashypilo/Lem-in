/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_roads_bhandary.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:07:57 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:20:47 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	int		efficiency_roads(int *arr, int ants)
{
	int			i;
	int			j;

	while (ants != 0)
	{
		i = 0;
		j = 0;
		while (arr[i] != -1)
		{
			if (arr[i] <= arr[j])
				j = i;
			i++;
		}
		arr[j] = arr[j] + 1;
		ants--;
	}
	return (arr[j] - 1);
}

static	int		*write_everything_roads(t_roads *r, int *arr)
{
	int			i;

	i = 0;
	while (r)
	{
		if (r->connect[1] != -1)
			arr[i++] = r->connect[0];
		r = r->next;
	}
	arr[i] = -1;
	return (arr);
}

static	int		*arrr_start_room(t_roads *r, int *arr, int end)
{
	int			i;

	i = 0;
	if (end == 0)
	{
		if (r->next)
		{
			while (r->next)
			{
				if (r->connect[1] != -1)
					arr[i++] = r->connect[0];
				r = r->next;
			}
			arr[i] = -1;
		}
		else
			arr = write_everything_roads(r, arr);
	}
	else
		arr = write_everything_roads(r, arr);
	return (arr);
}

static	int		check_best_roads(t_graf *g)
{
	int			*arr;
	int			ants;
	int			ants_new;

	arr = (int*)malloc(sizeof(int) * g->max_room);
	ants = g->ants;
	ants_new = g->ants;
	arr = arrr_start_room(g->start_road, arr, 0);
	ants = efficiency_roads(arr, ants);
	arr = arrr_start_room(g->start_road, arr, 1);
	ants_new = efficiency_roads(arr, ants_new);
	if (ants <= ants_new)
	{
		free(arr);
		return (0);
	}
	free(arr);
	return (1);
}

void			search_roads_bhandary(t_graf *g)
{
	int			stop;

	stop = 1;
	while (stop == 1)
	{
		if (superposition_bhandary(g, g->list_start) == 1)
		{
			if (g->swap_room != 1)
			{
				if (check_best_roads(g) == 0)
					stop = 0;
			}
		}
		else
			stop = 0;
		g->swap_room = 0;
	}
}
