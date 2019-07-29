/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:19:39 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/16 19:18:53 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static	int	search_link_next(char *line, int sim, int i)
{
	if (line[i] == sim)
	{
		i++;
		if (sim == ' ' && line[i] == '-')
			i++;
		if (ft_isalnum(line[i]))
		{
			if (sim == ' ')
			{
				while (ft_isdigit(line[i]) && line[i] != '\0')
					i++;
			}
			else
			{
				while ((ft_isalnum(line[i]) ||
							line[i] == '_') && line[i] != '\0')
					i++;
			}
			if (line[i] == '\0')
				return (0);
		}
	}
	return (1);
}

static	int	search_link(char *line, int sim, int i)
{
	while ((ft_isalnum(line[i]) || line[i] == '_') && line[i] != '\0')
		i++;
	if (line[i] == sim)
	{
		i++;
		if (sim == ' ' && line[i] == '-')
			i++;
		if (sim == ' ')
		{
			while (ft_isdigit(line[i]) && line[i] != '\0')
				i++;
		}
		else
		{
			while ((ft_isalnum(line[i]) || line[i] == '_') && line[i] != '\0')
				i++;
		}
		if (line[i] == '\0' && sim != ' ')
			return (0);
		if (search_link_next(line, sim, i) == 0)
			return (0);
	}
	else
		return (1);
	return (1);
}

int			search_links(char *line, int sim)
{
	int		i;

	i = 0;
	if (line[i] == 'L')
		return (1);
	if ((ft_isalnum(line[i]) || line[i] == '_') && line[i] != '\0')
	{
		if (search_link(line, sim, i) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (1);
	return (1);
}
