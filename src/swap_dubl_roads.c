/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_dubl_roads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:28:46 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 20:06:32 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	int	delete_busy_room(int *swap, int new, t_graf *g, int stop)
{
	int		j;
	int		i;
	int		k;

	i = 0;
	k = 0;
	j = g->swap_next;
	while (j != 0)
	{
		if (g->dooble_roads[new][j] == swap[0])
		{
			while (g->dooble_roads[new][j] == swap[k] && j != 0 && k != stop)
			{
				j--;
				k++;
			}
			g->swap_i = k - 1;
			i = j + 1;
		}
		if (j != 0)
			j--;
	}
	return (i);
}

static	int	seach_connect_room_in_roads(int *swap, int new, t_graf *g)
{
	int		j;
	int		i;
	int		k;

	k = 0;
	if (swap[0] != g->end)
	{
		i = delete_busy_room(swap, new, g, g->stop_swap);
		j = g->swap_next;
		while (j != g->dooble_roads[new][0])
		{
			if (g->dooble_roads[new][j] == swap[0])
				k = j;
			j++;
		}
		if (k < i && k != 0 && i != 0)
			return (k);
		else if (k != 0 && i != 0)
			return (i);
		if (i != 0 && k == 0)
			return (i);
		else if (k != 0 && i == 0)
			return (k);
	}
	return (g->swap_next);
}

static	int	*write_swap_rooms(int *swap, t_graf *g, int old, int new)
{
	int		i;
	int		j;

	if (g->dooble_roads[old][g->swap_start + 1] ==
			g->dooble_roads[new][g->swap_next - 1])
		i = g->swap_start + 1;
	else if (g->dooble_roads[old][g->swap_start - 1] ==
			g->dooble_roads[new][g->swap_next + 1])
		i = g->swap_start - 1;
	else
		i = g->swap_start;
	j = 0;
	while (i != g->dooble_roads[old][0])
		swap[j++] = g->dooble_roads[old][i++];
	swap[j] = g->end;
	swap[j + 1] = -1;
	g->stop_swap = j + 1;
	return (swap);
}

void		swap_dubl_roads(t_graf *g, int new_r, int old_r)
{
	int		*swap;
	int		i;
	int		j;

	swap = (int*)malloc(sizeof(int) * g->max_room);
	swap = write_swap_rooms(swap, g, old_r, new_r);
	j = g->swap_next;
	i = g->swap_start;
	while (j != g->dooble_roads[new_r][0])
		g->dooble_roads[old_r][i++] = g->dooble_roads[new_r][j++];
	g->dooble_roads[old_r][0] = i;
	g->dooble_roads[old_r][i] = g->end;
	g->dooble_roads[old_r][i + 1] = -1;
	g->swap_i = 0;
	j = seach_connect_room_in_roads(swap, new_r, g);
	i = g->swap_i;
	while (i != g->stop_swap)
		g->dooble_roads[new_r][j++] = swap[i++];
	g->dooble_roads[new_r][0] = j - 1;
	g->dooble_roads[new_r][j] = -1;
	free(swap);
}
