/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:42:25 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 19:17:52 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	void	write_ants(t_graf *g)
{
	int			i;

	i = 0;
	while (g->line[i] != '\0')
	{
		if ((g->line[i] < 48 || g->line[i] > 57))
			g->stop = 1;
		i++;
	}
	g->ants = ft_atoi(g->line);
	if (g->ants <= 0)
		g->stop = 1;
	g->space = -1;
	g->minus = 0;
}

static	void	validator(t_graf *g)
{
	if (ft_strncmp(g->line, "#Here", 4) == 0)
		g->number_lines = ft_atoi(&g->line[38]);
	else if ((ft_strcmp(g->line, "##start") == 0) && g->start == -2)
		g->start = -1;
	else if ((ft_strcmp(g->line, "##end") == 0) && g->end == -2)
		g->end = -1;
	else if (search_links(g->line, ' ') == 0 && g->space == -1)
		search_room_in_line(g);
	else if (search_links(g->line, '-') == 0 && g->minus == -1)
		getting_connections(g);
	else if (g->line[0] != '#' || (ft_strcmp(g->line, "##start") == 0)
		|| (ft_strcmp(g->line, "##end") == 0))
		g->stop = 1;
}

static	int		getting_data(int fd, t_graf *g, t_line *l)
{
	while (get_next_line(fd, &g->line) > 0)
	{
		l->line = ft_strdup(g->line);
		l->next = (t_line*)malloc(sizeof(t_line) * 1);
		l = l->next;
		l->next = NULL;
		if (g->ants == 0 && g->line[0] != '#')
			write_ants(g);
		else if (g->ants > 0)
			validator(g);
		else if (g->line[0] != '#' || (ft_strcmp(g->line, "##start") == 0)
			|| (ft_strcmp(g->line, "##end") == 0))
			g->stop = 1;
		free(g->line);
		if (g->stop == 1)
			return (1);
	}
	if (g->x == -1 || g->y == -1)
		return (1);
	return (0);
}

static int		start_lem_in(t_graf *g, t_line *l)
{
	if (g->start >= 0 && g->start_link == 0)
	{
		list_rooms(g);
		if (g->no_path == 0)
		{
			l = g->head_l;
			while (l->next)
			{
				ft_putstr(l->line);
				write(1, "\n", 1);
				l = l->next;
			}
			write(1, "\n", 1);
			start_ants(g, g->start_road);
		}
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

int				ft_lem_in(t_graf *g, int fd)
{
	t_line		*l;

	l = (t_line*)malloc(sizeof(t_line) * 1);
	l->next = NULL;
	g->head_l = l;
	if (getting_data(fd, g, l) == 1)
		return (1);
	else
	{
		if (start_lem_in(g, l) == 1)
			return (1);
	}
	return (0);
}
