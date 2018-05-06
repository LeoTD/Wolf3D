/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:52:56 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/06 04:38:08 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>

# include <stdio.h>
# include <unistd.h>

# define WOLF_ERROR(x, y) if (!(x)) sheep(y)

# define WIN_X 1024
# define WIN_Y 768

# define RED 16711680
# define GREEN 65280
# define BLUE 255
# define PURPLE 5387683
# define PINK 15024866
# define ORANGE 14380301
# define YELLOW 16120877

typedef struct			s_vector
{
	float		x;
	float		y;
}						t_vector;

typedef struct			s_pov
{
	t_vector	pos;
	t_vector	dir;
	t_vector	pln;
}						t_pov;

typedef struct			s_ray
{
	t_vector	dir;
	int			lheight;
	int			y_start;
	int			y_end;
}						t_ray;

typedef struct			s_vars
{
	int			map_x;
	int			map_y;
	t_vector	sid_dist;
	t_vector	del_dist;
	float		wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}						t_vars;

typedef struct			s_map
{
	int			height;
	int			width;
	int			**data;
}						t_map;

typedef struct			s_img
{
	void		*img;
	int			*data;

	int			color;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}						t_img;

typedef struct			s_wolf
{
	void		*mlx;
	void		*win;
	t_img		*img;

	t_map		*map;
	t_pov		pov;

}						t_wolf;

void					sheep(int errid);
void					draw_pixel(t_img *img, int x, int y, int color);
void					draw_vert(t_img *img, int x, int y_start, int y_end);
void					draw_pass(t_wolf *w);

void					map_init(t_wolf *w);
void					pov_init(t_pov *pov);
void					clear_img(t_img *img);
void					del_img(t_wolf *w, t_img **img);
t_img					*new_img(t_wolf *w, int width, int height);

int				g_temp_map[24][24];

#endif