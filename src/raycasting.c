/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 01:00:13 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/06 04:47:51 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			pov_init(t_pov *pov)
{
	pov->pos.x = 22;
	pov->pos.y = 12;
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
	
	//Calculate height of line to draw on screen
	r->lheight = (int)(WIN_Y / v->wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	r->y_start = -r->lheight / 2 + WIN_Y / 2;
	if (r->y_start < 0)
		r->y_start = 0;
	r->y_end = r->lheight / 2 + WIN_Y / 2;
	if (r->y_end >= WIN_Y)
		r->y_end = WIN_Y - 1;
}

static void		st_dda(t_vars *v)//, t_map *m)
{
	while (v->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
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
		//Check if ray has hit a wall
//		if (m->data[v->map_x][v->map_y] > 0)
		if (g_temp_map[v->map_x][v->map_y] > 0)
			v->hit = 1;
	}
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

		v.map_x = (int)w->pov.pos.x;
		v.map_y = (int)w->pov.pos.y;

		v.del_dist.x = fabs(1 / ray.dir.x);
		v.del_dist.y = fabs(1 / ray.dir.y);

		v.hit = 0;

//		Condensed form:
		v.step_x = (ray.dir.x < 0 ? -1 : 1);
		v.step_y = (ray.dir.y < 0 ? -1 : 1);
		v.sid_dist.x = (ray.dir.x < 0 ? w->pov.pos.x - v.map_x :
								v.map_x + 1.0 - w->pov.pos.x) * v.del_dist.x;
		v.sid_dist.y = (ray.dir.y < 0 ? w->pov.pos.y - v.map_y :
								v.map_y + 1.0 - w->pov.pos.y) * v.del_dist.y;
//		Expanded form:
/*		if (ray.dir.x < 0)
		{
			v.step_x = -1;
			v.sid_dist.x = (w->pov.pos.x - v.map.x) * v.del_dist.x;
		}
		else
		{
			v.step_x = 1;
			v.sid_dist.x = (v.map.x + 1.0 - w->pov.pos.x) * v.del_dist.x;
		}
		if (ray.dir.y < 0)
		{
			v.step_y = -1;
			v.sid_dist.y = (w->pov.pos.y - v.map.y) * v.del_dist.y;
		}
		else
		{
			v.step_y = 1;
			v.sid_dist.y = (v.map.y + 1.0 - w->pov.pos.y) * v.del_dist.y;
		}*/

		st_dda(&v);//, w->map);

		st_calc_distance(&w->pov, &v, &ray);

		w->img->color = PURPLE;
		if (v.side == 1)
			w->img->color /= 2;
		draw_vert(w->img, x, ray.y_start, ray.y_end);

//		draw_column(mlx, &ray, x);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img->img, 0, 0);
}
