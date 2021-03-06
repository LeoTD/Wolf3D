/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:52:56 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/07 08:11:58 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>

# include <unistd.h>
# include <time.h>

# define WOLF_ERROR(x, y) if (!(x)) sheep(y)

# define WIN_X 1024
# define WIN_Y 768

# define VIEW_DISTANCE 10
# define COLOR_FALLOFF 0x010707

# define RED 0xff0000
# define GREEN 0xff00
# define BLUE 0xff
# define PURPLE 5387683
# define PINK 15024866
# define ORANGE 14380301
# define YELLOW 16120877

# define SKY_COLOR 0x89b6ff
# define FLOOR_COLOR 0x2d251a

# define ESC_KEY 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125

# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define W_KEY 13

# define KEY_PRESS_MASK (1L<<0)
# define KEY_DOWN 2
# define KEY_UP 3
# define WINDOW_CLOSE 17

# define TURN_SPEED 0.03f
# define MOVE_SPEED 0.05f

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
	char		up;
	char		down;
	char		left;
	char		right;
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
	char		rave;
}						t_img;

typedef struct			s_wolf
{
	void		*mlx;
	void		*win;
	t_img		*img;

	t_map		*map;
	t_pov		pov;

}						t_wolf;

int						sheep(int errid);
void					draw_pixel(t_img *img, int x, int y, int color);
void					draw_vert(t_img *img, int x, int y_start, int y_end);
int						draw_pass(t_wolf *w);
int						color_picker(t_ray *ray, t_vars *v);
int						view_fade(int color, float wall_dist);

int						key_up(int key_id, t_wolf *w);
int						key_down(int key_id, t_wolf *w);
int						loop_handler(t_wolf *w);
void					movement(t_wolf *w, float move_speed);
void					rotate_pov(t_pov *p, float angle);

void					map_init(t_wolf *w);
void					pov_init(t_pov *pov);
void					clear_img(t_img *img);
void					del_img(t_wolf *w, t_img **img);
t_img					*new_img(t_wolf *w, int width, int height);

int				g_temp_map[24][24];

#endif
