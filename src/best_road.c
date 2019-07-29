/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_road.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:27:41 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 18:30:39 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static int		efficiency(int *arr, int ants)
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

static int		*arr_new_road(t_graf *g, int *arr)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	while (i < g->stop)
	{
		arr[k++] = g->dooble_roads[i][0];
		i++;
	}
	arr[k] = -1;
	return (arr);
}

static int		*arr_old_roads(t_roads *r, int *arr)
{
	int			i;

	i = 0;
	while (r->next)
	{
		if (r->connect[1] != -1)
			arr[i++] = r->connect[0];
		r = r->next;
	}
	arr[i] = -1;
	return (arr);
}

int				best_roads(t_graf *g)
{
	int			*arr;
	int			ants;
	int			ants_new;

	arr = (int*)malloc(sizeof(int) * g->max_room);
	ants = g->ants;
	ants_new = g->ants;
	arr = arr_old_roads(g->start_road, arr);
	ants = efficiency(arr, ants);
	arr = arr_new_road(g, arr);
	ants_new = efficiency(arr, ants_new);
	if (ants_new < ants)
	{
		free(arr);
		return (1);
	}
	free(arr);
	return (0);
}
