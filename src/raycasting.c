/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 01:00:13 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/06 22:54:44 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			pov_init(t_pov *pov)
{
	pov->pos.x = 7;
	pov->pos.y = 7;
	pov->dir.x = 1.0f;
	pov->dir.y = 0.0f;
	pov->pln.x = 0.0f;
	pov->pln.y = 2.0f / 3.0f;
}

static void		st_calc_distance(t_pov *p, t_vars *v, t_ray *r)
{
	if (v->side == 0)
		v->wall_dist = (v->map_x - p->pos.x + (1 - v->step_x) / 2) / r->dir.x;
	else
		v->wall_dist = (v->map_y - p->pos.y + (1 - v->step_y) / 2) / r->dir.y;
	r->lheight = (int)(WIN_Y / v->wall_dist);
	r->y_start = -r->lheight / 2 + WIN_Y / 2;
	if (r->y_start < 0)
		r->y_start = 0;
	r->y_end = r->lheight / 2 + WIN_Y / 2;
	if (r->y_end >= WIN_Y)
		r->y_end = WIN_Y - 1;
}

static void		st_dda(t_vars *v)
{
	while (v->hit == 0)
	{
		if (v->sid_dist.x < v->sid_dist.y)
		{
			v->sid_dist.x += v->del_dist.x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->sid_dist.y += v->del_dist.y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (g_temp_map[v->map_x][v->map_y] > 0)
			v->hit = 1;
	}
}

static void		st_prep_vars(t_vars *v, t_wolf *w, t_ray *ray)
{
	v->map_x = (int)w->pov.pos.x;
	v->map_y = (int)w->pov.pos.y;
	v->del_dist.x = fabs(1 / ray->dir.x);
	v->del_dist.y = fabs(1 / ray->dir.y);
	v->hit = 0;
	v->step_x = (ray->dir.x < 0 ? -1 : 1);
	v->step_y = (ray->dir.y < 0 ? -1 : 1);
	v->sid_dist.x = (ray->dir.x < 0 ? w->pov.pos.x - v->map_x :
							v->map_x + 1.0 - w->pov.pos.x) * v->del_dist.x;
	v->sid_dist.y = (ray->dir.y < 0 ? w->pov.pos.y - v->map_y :
							v->map_y + 1.0 - w->pov.pos.y) * v->del_dist.y;
}

static int		st_color_fade(int color, int k, int mask)
{
	int			tmp;

	tmp = color & mask;
	tmp -= ((COLOR_FALLOFF & mask) * k);
	if (tmp < 0)
		tmp = 0;
	return (tmp);
}

static int		st_view_fade(int color, float wall_dist)
{
	float			tmp;

	tmp = 0;
	tmp += st_color_fade(color, (int)(wall_dist - VIEW_DISTANCE), RED);
	tmp += st_color_fade(color, (int)(wall_dist - VIEW_DISTANCE), GREEN);
	tmp += st_color_fade(color, (int)(wall_dist - VIEW_DISTANCE), BLUE);
	return (tmp);
}

int				color_picker(t_ray *ray, t_vars *v)
{
	int			tmp;

	tmp = 0;
	if (v->side == 1)
		if (ray->dir.y < 0)
			tmp = 0x012E57;
		else
			tmp = 0x93b7c6;
	else
		if (ray->dir.x < 0)
			tmp = 0x001528;
		else
			tmp = 0x96128b;
	if (v->wall_dist > VIEW_DISTANCE + 1)
		tmp = st_view_fade(tmp, v->wall_dist);
	return (tmp);
}

void			draw_pass(t_wolf *w)
{
	int			x;
	t_ray		ray;
	t_vars		v;
	float		camera;

	clear_img(w->img);
	x = -1;
	while (++x < WIN_X)
	{
		camera = 2.0f * x / WIN_X - 1.0f;
		ray.dir.x = w->pov.dir.x + w->pov.pln.x * camera;
		ray.dir.y = w->pov.dir.y + w->pov.pln.y * camera;
		st_prep_vars(&v, w, &ray);
		st_dda(&v);
		st_calc_distance(&w->pov, &v, &ray);
		w->img->color = color_picker(&ray, &v);
		draw_vert(w->img, x, ray.y_start, ray.y_end);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img->img, 0, 0);
}
