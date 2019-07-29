/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashypilo <ashypilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:42:04 by ashypilo          #+#    #+#             */
/*   Updated: 2019/07/24 19:17:33 by ashypilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef	struct		s_line
{
	char			*line;
	struct s_line	*next;
}					t_line;

typedef	struct		s_coord
{
	int				room;
	int				x;
	int				y;
	struct s_coord	*next;
}					t_coord;

typedef	struct		s_room
{
	int				room;
	int				head_room;
	int				head;
	int				was;
	int				not_room;
	int				depth;
	int				depth_cross;
	int				start;
	int				stop;
	int				end;
	int				room_busy;
	struct s_room	*next;
	struct s_link	*con;
	struct s_perent	*per;
}					t_room;

typedef	struct		s_link
{
	t_room			*link;
	int				depth;
	int				was;
	struct s_link	*next;
	struct s_room	*perent;
}					t_link;

typedef	struct		s_perent
{
	t_room			*link;
	struct s_perent	*perent;
	struct s_perent	*next;
}					t_perent;

typedef	struct		s_roads
{
	int				room;
	int				start;
	int				end;
	int				turn;
	int				*connect;
	int				*mov_ant;
	int				busy;
	struct s_roads	*next;
	struct s_roads	*prev;

}					t_roads;

typedef struct		s_graf
{
	t_room			*head_rm;
	t_room			*list_head;
	t_room			*list_start;
	t_room			*list_end;
	t_room			*prev_list_room;
	t_roads			*start_road;
	t_room			*list_search;
	t_roads			*swap_roads;
	t_roads			*roads_end;
	t_room			*start_list_room;
	t_perent		*start_rd;
	t_coord			*coordinate;
	t_coord			*end_c;
	t_line			*head_l;
	int				used_roads;
	int				used_roads_new;
	int				swap_start;
	int				swap_next;
	int				swap_room;
	int				head;
	int				stop;
	int				short_road;
	int				*depth_roads;
	int				**coord_x;
	int				**coord_y;
	int				**coord_x_m;
	int				**coord_y_m;
	int				**dooble_roads;
	int				big_roads;
	int				swap_i;
	int				stop_swap;
	int				size_minus;
	int				no_path;
	int				start_link;
	int				x;
	int				y;
	int				rooms;
	int				connect;
	int				size;
	int				size_connect;
	int				prev_room;
	int				start;
	int				end;
	int				num;
	int				ants;
	char			*line;
	char			**int_rooms;
	int				max_room;
	int				**matrix;
	int				space;
	int				minus;
	int				number_lines;
	int				coord;
}					t_graf;

int					ft_lem_in(t_graf *g, int fd);
int					search_links(char *line, int sim);
void				search_room_in_line(t_graf *g);
void				malloc_matrix_coordinate(t_graf *g);
void				malloc_arrays(t_graf *g);
int					**more_coordinate(int **arr_old, int size);
int					coord_plus(t_graf *g, int x, int y, int i);
int					coord_minus(t_graf *g, int x, int y);
void				getting_connections(t_graf *g);
void				list_rooms(t_graf *g);
void				search_the_way(t_graf *g, t_room *rm);
void				search_roads_bhandary(t_graf *g);
int					superposition_bhandary(t_graf *g, t_room *rm);
t_perent			*r_busy(t_graf *g, t_room *rm, t_perent *rd, t_perent *pr);
int					write_new_road(t_graf *g, t_room *rm, t_perent *rd);
int					swap_roads(t_graf *g, t_roads *r);
void				swap_dubl_roads(t_graf *g, int new_r, int old_r);
int					best_roads(t_graf *g);
void				start_ants(t_graf *g, t_roads *r);
t_roads				*sorting_roads(t_graf *g);
void				create_arr_move_ant(t_graf *g, t_roads *r);
void				start_ants_on_the_roads(t_graf *g, t_roads *r);
void				moving_ants(t_graf *g, t_roads *r);

#endif
